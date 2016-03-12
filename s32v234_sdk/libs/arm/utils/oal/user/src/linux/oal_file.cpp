/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
/**
* \file OalFile.cpp
* \brief OAL file operations implementation
* \author Igor Aleksandrowicz
* \version
* \date 31-July-2013
****************************************************************************/

#include <oal_file.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <cerrno>
#include <cstdio>
#include <dirent.h>
#include <ftw.h>

/*****************************************************************************
* constants
*****************************************************************************/

//mode used when creating new files / directories
const int FILE_CREATION_MODE = S_IRUSR | S_IWUSR;
const int DIRECTORY_CREATION_MODE = S_IRUSR | S_IWUSR | S_IXUSR;

/*****************************************************************************
* local functions
*****************************************************************************/

/****************************************************************************/
/** Translates the errno to OAL file error.
*
* \return OAL file error
*
* \todo may be not complete
*****************************************************************************/
static LIB_RESULT FileErrorTranslate()
{
  LIB_RESULT ret = LIB_FAILURE;

  switch(errno)
  {
    case EACCES:
    case EPERM:
      ret = OAL_ERR_FILE_ACCESS;
      break;
    case EEXIST:
      ret = OAL_ERR_FILE_EXISTS;
      break;
    case ENOSPC:
    case EDQUOT:
    case EFBIG:
      ret = OAL_ERR_FILE_OUT_OF_SPACE;
      break;
    //outside addressing space?
    case EFAULT:
      ret = OAL_ERR_FILE_ACCESS;
      break;
    case ENAMETOOLONG:
    //if directory
    case EISDIR:
    //if not directory
    case ENOTDIR:
      ret = OAL_ERR_INVALID_FILE_PATH;
      break;
    //apparently NOT EBAFD
    case EBADF:
    //fd ok but not for read/write requested
    case EINVAL:
      ret = OAL_ERR_INVALID_FILE_DESCRIPTOR;
      break;
    case EIO:
      ret = OAL_ERR_FILE_IO;
      break;
    //seek outside?
    case EOVERFLOW:
      ret = OAL_ERR_FILE_IO;
      break;
    case ENOENT:
      ret = OAL_ERR_NO_FILE;
      break;
    default:
      break;
  }

  return ret;
}

/*****************************************************************************
* functions
*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

LIB_RESULT OAL_FileOpen(OAL_FILE_DESCRIPTOR *fd, const char *pFilePath,
    unsigned int AccessType)
{
  int linux_flags = O_CLOEXEC;

  //TODO: other 2 flags
  if (AccessType & OAL_FILE_RDONLY)
  {
    linux_flags |= O_RDONLY;
  }
  if (AccessType & OAL_FILE_WRONLY)
  {
    linux_flags |= O_WRONLY;
  }
  if (AccessType & OAL_FILE_RDWR)
  {
    linux_flags |= O_RDWR;
  }
  if (AccessType & OAL_FILE_APPEND)
  {
    linux_flags |= O_APPEND;
  }
  if (AccessType & OAL_FILE_CREATE)
  {
    linux_flags |= O_CREAT;
  }
  if (AccessType & OAL_FILE_TRUNC)
  {
    linux_flags |= O_TRUNC;
  }

  int ret = open(pFilePath, linux_flags, FILE_CREATION_MODE);

  LIB_RESULT lret = LIB_SUCCESS;
  if (ret < 0)
  {
    lret = FileErrorTranslate();
  }
  else
  {
    fd->fd = ret;
  }

  return lret;
}

LIB_RESULT OAL_FileClose(OAL_FILE_DESCRIPTOR *fd)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if(close(fd->fd) < 0)
  {
    ret = FileErrorTranslate();
  }

  return ret;
}

LIB_RESULT OAL_FileWrite(OAL_FILE_DESCRIPTOR *fd, char* pData,
    unsigned int length, unsigned int* BytesWritten)
{
  LIB_RESULT ret = LIB_SUCCESS;

  //TODO: check permissions?
  int bw = (int)write(fd->fd, pData, length);
  if (bw < (int)length)
  {
    ret = FileErrorTranslate();
  }
  else if(BytesWritten)
  {
    *BytesWritten = (unsigned int)bw;
  }

  return ret;
}

LIB_RESULT OAL_FileRead(OAL_FILE_DESCRIPTOR *fd, char* pData,
    unsigned int length, unsigned int* BytesRead)
{
  LIB_RESULT ret = LIB_SUCCESS;

  //TODO: check permissions?
  int br = (int)read(fd->fd, (void*)pData, length);
  if (br < 0)
  {
    ret = FileErrorTranslate();
  }
  else if (BytesRead)
  {
    *BytesRead = (unsigned int)br;
  }

  return ret;
}

LIB_RESULT OAL_FileSeek(OAL_FILE_DESCRIPTOR *fd, long long offset,
    unsigned int mark, unsigned int *position)
{
  //TODO: fill with invalid value?
  int whence = 0;
  switch (mark)
  {
    case FILE_START_MARK:
      whence = SEEK_SET;
      break;
    case FILE_END_MARK:
      whence = SEEK_END;
      break;
    case FILE_CURRENT_MARK:
      whence = SEEK_CUR;
      break;
    default:
      break;
  }

  LIB_RESULT lret = LIB_SUCCESS;

  int ret = lseek(fd->fd, (off_t)offset, whence);
  if (ret < 0)
  {
    lret = FileErrorTranslate();
  }
  else if (position)
  {
    *position = (unsigned int)ret;
  }

  return lret;
}

LIB_RESULT OAL_FileSeekRead(OAL_FILE_DESCRIPTOR *fd, long long offset,
    unsigned int mark, unsigned int *position, char* pData, unsigned int length,
    unsigned int* BytesRead)
{
  LIB_RESULT result = OAL_FileSeek(fd, offset, mark, position);
  if (result == LIB_SUCCESS)
  {
    result = OAL_FileRead(fd, pData, length, BytesRead);
  }

  return result;
}

LIB_RESULT OAL_FileDelete (const char *pFilePath)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (unlink(pFilePath))
  {
    ret = FileErrorTranslate();
  }

  return ret;
}

//TODO: next 2 functions should work but report wrong numbers in VirutalBox...
LIB_RESULT OAL_FileGetFreeSpace (char *pPath,
    unsigned long long *pFreeSpace)
{
  LIB_RESULT ret = LIB_SUCCESS;

  struct statvfs stats;
  if (statvfs(pPath, &stats))
  {
    ret = FileErrorTranslate();
  }
  else
  {
    //TODO: use f_avail?
    *pFreeSpace = stats.f_bsize * stats.f_bfree;
  }

  return ret;
}

LIB_RESULT OAL_FileGetTotalSpace (char *pFilePath,
    unsigned long long *pTotalSpace)
{
  LIB_RESULT ret = LIB_SUCCESS;

  struct statvfs stats;
  if (statvfs(pFilePath, &stats))
  {
    ret = FileErrorTranslate();
  }
  else
  {
    *pTotalSpace = stats.f_frsize * stats.f_blocks;
  }

  return ret;
}

LIB_RESULT OAL_FileRename (char *pOldFilePath, char *pNewFilePath)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (rename(pOldFilePath, pNewFilePath))
  {
    ret = FileErrorTranslate();
  }

  return ret;
}

LIB_RESULT OAL_FileGetAttributes (char *,
    OAL_FILE_ATTRIBUTES *pAttributes)
{
  //TODO: not really implemented... map user permissions into attributes?
  pAttributes->as32Bits = 0;
  pAttributes->attr.normal = 1;
  return LIB_SUCCESS;
}

LIB_RESULT OAL_FileSetAttributes (char *,
    OAL_FILE_ATTRIBUTES *)
{
  //TODO: not really implemented... map attributes into user attributes?
  return LIB_SUCCESS;
}

LIB_RESULT OAL_FileSetCurrentWorkingDirectory(char *pFilePath)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (chdir(pFilePath))
  {
    ret = FileErrorTranslate();
  }

  return ret;
}

LIB_RESULT OAL_FileGetDirectoryEntryCount(char *pFilePath, unsigned int *pCount)
{
  LIB_RESULT ret = LIB_SUCCESS;

  DIR *dir;

  dir = opendir(pFilePath);
  if (!opendir(pFilePath))
  {
    ret = FileErrorTranslate();
  }
  else
  {
    bool ok = true;
    dirent* de = 0;
    unsigned int count = 0;
    do
    {
      de = readdir(dir);
      if ((long)de < 0)
      {
        ok = false;
        break;
      }
      ++count;
    } while((long)de > 0);

    if (ok && closedir(dir))
    {
      ok = false;
    }

    if (!ok)
    {
      ret = FileErrorTranslate();
    }
    else
    {
      *pCount = count;
    }
  }

  return ret;
}

/*
 * TODO: directory listing functions not implemented, directory open function
 * missing -> other functions unusable
*/

/*
 * TODO:
 * other functions... some of the remaining prototypes are strange (e.g. dealing
 * with volume labeling) by a drive letter, duplicated entries (erase directory
 * and two delete directory functions)
*/

LIB_RESULT OAL_FileCopy (char *sourceFilePath, char *destFilePath)
{
  OAL_FILE_DESCRIPTOR source;
  OAL_FILE_DESCRIPTOR destination = {0, 0, 0, 0};
  

  LIB_RESULT lr;

  lr = OAL_FileOpen(&source, sourceFilePath, OAL_FILE_RDONLY);
  if (lr != LIB_SUCCESS)
  {
    lr = FileErrorTranslate();
    OAL_FileClose(&destination);
  }
  else
  {
    lr = OAL_FileOpen(&destination, destFilePath,
        OAL_FILE_WRONLY | OAL_FILE_CREATE);
    if (lr != LIB_SUCCESS)
    {
      lr = FileErrorTranslate();
      OAL_FileClose(&source);
      OAL_FileClose(&destination);
    }
    else
    {

      //TODO: use (expected?) block size?
      const unsigned int bufferSize = 4096;
      char buffer[bufferSize];

      //TODO: check reads/writes and closing?
      unsigned int bytesRead = bufferSize;
      unsigned int bytesWritten = bufferSize;

      while (bytesRead == bufferSize)
      {
        //let's be safe
        bytesRead = 0;
        lr = OAL_FileRead(&source, buffer, bufferSize, &bytesRead);
        if (lr == LIB_SUCCESS)
        {
          lr = OAL_FileWrite(&destination, buffer, bytesRead, &bytesWritten);
        }

        if (lr != LIB_SUCCESS)
        {
          break;
        }
      }

      if (lr == LIB_SUCCESS)
      {
        lr = OAL_FileClose(&source);
        LIB_RESULT tlr = OAL_FileClose(&destination);
        if (tlr != LIB_SUCCESS)
        {
          lr = tlr;
        }
      }
    }
  }

  return lr;
}

LIB_RESULT FileSystemRegisterTaskWithFS(void)
{
  return LIB_SUCCESS;
}

LIB_RESULT FileSystemDeRegisterTaskWithFS(void)
{
  return LIB_SUCCESS;
}

LIB_RESULT OAL_FileCreateDirectory(char *pFilePath)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (mkdir(pFilePath, DIRECTORY_CREATION_MODE))
  {
    ret = FileErrorTranslate();
  }

  return ret;
}

LIB_RESULT OAL_FileDeleteDirectory(char *pFilePath)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (rmdir(pFilePath))
  {
    ret = FileErrorTranslate();
  }

  return ret;
}

/*
 * TODO: the same as delete from the documentation but maybe should delete
 * the files???
 */
LIB_RESULT OAL_FileEraseDirectory(char *pFilePath)
{
  return OAL_FileDeleteDirectory(pFilePath);
}

//deleting function required by ntfw
static int unlink_cb(const char *fpath, const struct stat *,
    int, struct FTW *)
{
    int rv = remove(fpath);

    return rv;
}

LIB_RESULT OAL_DirDeleteRecursively(char *name)
{
  LIB_RESULT ret = LIB_SUCCESS;

  if (nftw(name, unlink_cb, 64, FTW_DEPTH | FTW_PHYS))
  {
    ret = FileErrorTranslate();
  }

  return ret;
}

#ifdef __cplusplus
}
#endif
