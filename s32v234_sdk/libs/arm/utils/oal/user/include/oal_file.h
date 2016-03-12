/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2010 All right reserved.
 *  
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

#ifndef __OAL_FILE_H__
#define __OAL_FILE_H__

#include <stdlib.h>
#include <time.h>
#include <global_errors.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define __T5_USE_ADVANCED_FAT__

////////////////////////////////////////////////////////////////////////
/// \file OalFile.h
/// \brief Interface definition for OAL file system
/// \addtogroup OAL_File OAL File System
/// @{
////////////////////////////////////////////////////////////////////////

#define OAL_MAX_FILE_PATH_LEN            (512+7) 

/// Structure of Date and Time
/**
 * \b month: 1-12.
 * \n\b day: 1-31.
 * \n\b year: years since 1900 .
 * \n\b hour: 0-23.
 * \n\b minute: 0-59.
 * \n\b second: 0-59.
 */
typedef struct
{
   unsigned char  month;      ///< 1-12
   unsigned char  day;        ///< 1-31
   unsigned char  year;       ///< years since 1900
   unsigned char  hour;       ///< 0-23
   unsigned char  minute;     ///< 0-59
   unsigned char  second;     ///< 0-59
} OAL_DATE_TIME;

/// Structure of file descriptor
/**
 * \b fd: File ID used by file system.
 * \n\b driveNum: Drive number 0: RAM, disk 2: SDcard, 3 NAND Flash.
 * \n\b txChannelId: Used by AMPI.
 * \n\b rxChannelId: Used by AMPI.
 */
typedef struct
{
   int                     fd;               ///< File ID, used by file system
   int                     driveNum;         ///< Drive number. 0: RAM disk. 2: SDcard. 3 NAND Flash.
   unsigned short          txChannelId;      ///< Do not set, used by AMPI
   unsigned short          rxChannelId;      ///< Do not set, used by AMPI
} OAL_FILE_DESCRIPTOR;


typedef union
{
   struct writeCmd_t
   {
      unsigned int  cmd;
      unsigned int  blocking;
      LIB_RESULT    resultCode;
      unsigned int  length;
      int           bytesWritten;
   } write_cmd;
   struct readCmd_t
   {
      unsigned int  cmd;
      unsigned int  blocking;
      LIB_RESULT    resultCode;
      unsigned int  length;
      char         *pReadBuffer;
      unsigned int  bytesRead;
   } read_cmd;
   struct seekCmd_t
   {
      unsigned int  cmd;
      unsigned int  blocking;
      LIB_RESULT    resultCode;
      long long           offset;
      unsigned int  mark;
      unsigned int           position;
   } seek_cmd;
   struct tellCmd_t
   {
      unsigned int  cmd;
      unsigned int  blocking;
      LIB_RESULT    resultCode;
      unsigned int           position;
   } tell_cmd;
   struct closeCmd_t
   {
      unsigned int  cmd;
      unsigned int  blocking;
      LIB_RESULT    resultCode;
   } close_cmd;
}OAL_FILE_TASK_OPERATION;

typedef struct
{
   unsigned int            blockStartFptr; 
   unsigned int            blockEndFptr;
   unsigned int            blockChanged;
} CACHE_STATUS;

/// bitflags to use when setting file time or attributes
typedef enum
{
    OAL_FILE_SET_CREATED_TIME  = 0x01,  ///< set created time only
    OAL_FILE_SET_UPDATED_TIME  = 0x02,	 ///< set Updated time only
    OAL_FILE_SET_ACCESSED_DATE = 0x04,  ///< set accessed date 
    OAL_FILE_SET_ATTRIBUTE     = 0x08   ///< set attribute
} OAL_FILE_SET_COMMANDS;


// Literals
#define OAL_FILE_RDONLY             0x00000001 ///<\if MMPAPIsOnly For read-only access \endif
#define OAL_FILE_WRONLY             0x00000002 ///<\if MMPAPIsOnly For write-only access \endif
#define OAL_FILE_RDWR               0x00000004 ///<\if MMPAPIsOnly For read-write access \endif
#define OAL_FILE_APPEND             0x00000008 ///<\if MMPAPIsOnly Writes will append to the end of the file \endif
#define OAL_FILE_CREATE             0x00000010 ///<\if MMPAPIsOnly Create the file if it does not exist \endif
#define OAL_FILE_TRUNC              0x00000020 ///<\if MMPAPIsOnly Truncate the file if it exists \endif
#define OAL_FILE_SETACC_RDONLY      0x00010000 ///<\if MMPAPIsOnly To set read-only filesystem permissions for the file \endif
#define OAL_FILE_SETACC_RDWR        0x00020000 ///<\if MMPAPIsOnly To set read-write filesystem permissions for the file \endif

/// OAL File Task commands 
typedef enum
{
   OAL_FILE_WRITE_CMD             = 0x0001, ///<\if MMPAPIsOnly Write command to a task \endif
   OAL_FILE_CLOSE_CMD             = 0x0002, ///<\if MMPAPIsOnly Close command to a task \endif
   OAL_FILE_CLOSE_NO_FLUSH_CMD    = 0x0003, ///<\if MMPAPIsOnly Close No Flush command to a task \endif
   OAL_FILE_SEEK_CMD              = 0x0004, ///<\if MMPAPIsOnly Seek command to a task \endif
   OAL_FILE_TELL_CMD              = 0x0005, ///<\if MMPAPIsOnly Tell command to a task \endif
   OAL_FILE_READ_CMD              = 0x0006  ///<\if MMPAPIsOnly READ command to a task \endif
} OAL_FILE_TASK_CMD;

#define OAL_FILE_TASK_CMD_DEFAULT_TIMEOUT     (1000*OAL_MUSEC_PER_TICK)

#define FILE_START_MARK             0       ///<\if MMPAPIsOnly File start marker \endif
#define FILE_END_MARK               1       ///<\if MMPAPIsOnly File end marker \endif
#define FILE_CURRENT_MARK           2       ///<\if MMPAPIsOnly File current position marker \endif

/// DOS file attributes
/**
 * This is bit filed representation.
 * \n\b normal: If 1, the file is an ordinary file.
 * \n\b readOnly: If 1, file is a read only file and indicates that writes to the file should fail.
 * \n\b hidden:  If 1, file is invisible by file browser and indicates that normal directory listings should not show this file. 
 * \n\b system: if 1, the file is an operating system file.
 * \n\b volume: There should only be one "file" on the volume that has this attribute set, 
 * and that file must be in the root directory. This name of this file is actually the label for the volume. 
 * \n\b directory: If 1, the file is a directory and indicates that this file is actually a container for other files.
 * \n\b archive:  If 1, the file is an archive file which supports backup utilities. 
 * This bit is set by the FAT file system driver when a file is created, renamed, or written to. 
 * Backup utilities may use this attribute to indicate which files on the volume have been modified since the last time that a backup was performed.
 * \n\b reserved: Unused bits. 
 */
typedef union
{
   struct
   {
      unsigned int normal     : 1;     /**< Writable file */
      unsigned int readOnly   : 1;     /**< Read Only file */
      unsigned int hidden     : 1;     /**< Hidden from directory view */
      unsigned int system     : 1;     /**< Owned by the operating system */
      unsigned int volume     : 1;     /**< Volume label entry */
      unsigned int directory  : 1;     /**< Sub-directory */
      unsigned int archive    : 1;     /**< Copy of the file exists on this or another medium */
      unsigned int reserved   : 25;    /**< Reserved */
   } attr;                             /**< Bitflags to use when setting file attributes */
   unsigned int    as32Bits;           /**< Unsigned int represetation */
} OAL_FILE_ATTRIBUTES;

typedef unsigned int  OAL_DIRECTORY_HANDLE; ///< Directory handle type define

#define DIR_HANDLE_FW_MAGIC_HEADER       0x44495248     //DIRH forward
#define DIR_HANDLE_BW_MAGIC_HEADER       0x48524944     //HRID backward

/// T5_USE_ADVANCED_FAT SYSTEM
typedef enum T5_FAT_FILE_ATTRIBUTE_TYPE
{
   T5_FILE_TYPE_NORMAL     = 0,        /**< Writable file */
   T5_FILE_TYPE_RDONLY     = 0x01,     /**< Read Only file */
   T5_FILE_TYPE_HIDDEN     = 0x02,     /**< Hidden from directory view */
   T5_FILE_TYPE_SYSTEM     = 0x04,     /**< Owned by the operating system */
   T5_FILE_TYPE_VOLUME     = 0x08,     /**< Volume label entry */
   T5_FILE_TYPE_DIR        = 0x10,     /**< Sub-directory */
   T5_FILE_TYPE_ARCHIVE    = 0x20      /**< Copy of the file exists on this or another medium */
} T5_FAT_FILE_ATTRIBUTE_TYPE;

typedef struct
{
   T5_FAT_FILE_ATTRIBUTE_TYPE st_mode; /**< File or directory attributes */
   unsigned long              st_size; /**< File size in bytes */
   time_t                     st_time; /**< Timestamp of last modification */
#ifdef __T5_USE_ADVANCED_FAT__
   unsigned char        fattribute;    /**< File attributes */
   unsigned char        fcrcmsec;      /**< File create centesimal mili second */
   unsigned short       fcrtime;       /**< File create time */
   unsigned short       fcrdate;       /**< File create date */
   unsigned short       faccdate;      /**< Access date */
   unsigned short       fuptime;       /**< File update time */
   unsigned short       fupdate;       /**< File update */
   unsigned long        fsize;         /**< File size */
   unsigned long        alloced_size;  /**< Size rounded up to the hearest cluster */
   unsigned short       opencount;     /**<  KIMBC   2007.05.08  */
#endif
} T5_FAT_FILE_STAT_STRUCT;

/// Structure of directory entry
/**
 *
 * This is bit filed representation.
 * \n\b name[MMP_MAX_FILE_PATH_LEN]: Long file name, maximum 256 characters.
 * \n\b shortName[12]: Short file name: short name need  8+1(null data byte)bytes, but adjusted to align on 4 byte boundary
 * \n\b extension[4]:  Extension
 * \n\b size: The size of file in bytes    
 * \n\b dateTime: Modified date and time. 
 * \n\b createdTime: Created date and time
 * \n\b attrib: File attribute, Ex. read only file, archive file so on...
 * \n\b firstClustorNumber: First cluster number in the physical location on local file system  
 */
 
typedef struct
{
   char                 name[OAL_MAX_FILE_PATH_LEN + 1];  ///< File path includeing directory
   char                 shortName[12];                    ///< Short name need  8+1(null data byte)  byte,but adjust aline 4byte
   char                 extension[4];                     ///< Extension
   unsigned int         size;                             ///< The size of file
   OAL_DATE_TIME        dateTime;		                   ///< Update time
   OAL_DATE_TIME        createdTime;	                   ///< Created time
   OAL_FILE_ATTRIBUTES  attrib;                           ///< The file attribute
#ifdef __T5_USE_ADVANCED_FAT__
   T5_FAT_FILE_STAT_STRUCT  stat;                         ///< T5 USE ADVANCED FAT SYSTEM
#endif
   unsigned int         firstClustorNumber;               ///< the first clustor Number in physical disk 
} OAL_DIRECTORY_ENTRY;

#define  OAL_FSFAT_12   0
#define  OAL_FSFAT_16   1
#define  OAL_FSFAT_32   2

typedef struct OAL_FILE_FORMAT_PARAMS_t
{
    unsigned char     partdisk;              ///< 1 : Partitioned disk, 0 : Not paritioned disk
    unsigned short    bytepsec;              ///< Bytes per sectors
    unsigned char     secpalloc;             ///< Sectors per cluster
    unsigned short    secreserved;           ///< Reserved sectors before the FAT
    unsigned char     numfats;               ///< Number of FATS on the disk
    unsigned short    numroot;               ///< Maximum # of root dir entries. FAT32 always 0
    unsigned char     mediadesc;             ///< Media descriptor byte
    unsigned short    secptrk;               ///< Sectors per track
    unsigned short    numhead;               ///< Number of heads
    unsigned short    numcyl;                ///< Number of cylinders
    unsigned int      totalsec;              ///< Total sectors
    char              oemname[9];            ///< Only first 8 bytes are used
    unsigned char     physical_drive_no;     ///< Boot Drive Information
                                             ///< 80h BootDrive  00h NotBootDrive
    unsigned int      binary_volume_label;   ///< Volume ID or Serial Number
    char              text_volume_label[12]; ///< Volume Label
    int               oal_fattype;
} OAL_FILE_FORMAT_PARAMS;

typedef struct
{
    unsigned long  secpcluster;
    unsigned long  bytepsec;
    unsigned long  freecluster;
    unsigned long  totalcluster;
} OAL_DISK_SPACE_STRUCT;


////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Open the specified file.
///
/// \param fd         - [out] Pointer to file descriptor
/// \param pFilePath  - [in] File path
/// \param AccessType - [in] File access type
///    - OAL_FILE_RDONLY
///    - OAL_FILE_WRONLY
///    - OAL_FILE_RDWR
///    - OAL_FILE_APPEND
///    - OAL_FILE_CREATE
///    - OAL_FILE_TRUNC
///    - OAL_FILE_SETACC_RDONLY
///    - OAL_FILE_SETACC_RDWR
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileOpen(OAL_FILE_DESCRIPTOR *fd, const char *pFilePath, unsigned int AccessType);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Close the specified file assuming the file descriptor is valid.
///
/// \param fd - [in] File descriptor
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileClose(OAL_FILE_DESCRIPTOR *fd);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Move to the specified location in an open file.
///
/// \param fd       - [in] File descriptor
/// \param offset   - [in] Offset from marker to seek to
/// \param mark     - [in] Marker
/// \param position - [out] Position after seek
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileSeek(OAL_FILE_DESCRIPTOR *fd, long long offset, unsigned int mark, unsigned int *position);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Read from an open file the number of specified bytes or whatever left
///  in the file.
///
/// \param fd        - [in] File descriptor
/// \param pData     - [in] Contents of the file will be read into the buffer referenced by pData
/// \param length    - [in] Number of bytes to be read
/// \param BytesRead - [out] Number of bytes actually read
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileRead(OAL_FILE_DESCRIPTOR *fd, char* pData, unsigned int length, unsigned int* BytesRead);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Seek to a specified location in a file, then read the specified
/// number of bytes or whatever remained in the file from the current position.
///
/// \param fd - [in] Pointer to file descriptor
/// \param offset     - [in] Offset from marker to seek to
/// \param mark       - [in] Marker
/// \param position   - [out] Position after seek
/// \param pData      - [out] Buffer to store data
/// \param length     - [in] Length of data to read
/// \param BytesRead  - [out] Number of bytes is read
///
/// \return
///    - #LIB_SUCCESS
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileSeekRead(OAL_FILE_DESCRIPTOR *fd, long long offset, unsigned int mark, unsigned int *position,
                            char* pData, unsigned int length, unsigned int* BytesRead);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// Write to an open file using the passing buffer with the number of
/// bytes specified.
///
/// \param fd           - [in] File descriptor
/// \param pData        - [in] Contents of the buffer referenced by pData will be written to the file
/// \param length       - [in] Number of bytes to be written
/// \param BytesWritten - [out] Number of bytes actually written
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileWrite(OAL_FILE_DESCRIPTOR *fd, char* pData, unsigned int length, unsigned int* BytesWritten);


////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Delete the specified file in the system.
///
/// \param pFilePath - [in] File path
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileDelete (const char *pFilePath);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Get free space on the specified drive.
///
/// \param pPath      - [in] Drive letter
/// \param pFreeSpace - [out] Free space on drive
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileGetFreeSpace (char *pPath, unsigned long long *pFreeSpace);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Get Total space on the specified drive.
///
/// \param pFilePath      - [in] Drive letter
/// \param pTotalSpace - [out] Total space on drive
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileGetTotalSpace (char *pFilePath, unsigned long long *pTotalSpace);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Re-name one file to another file.
///
/// \param pOldFilePath - [in] Old file path
/// \param pNewFilePath - [in] New file path
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileRename (char *pOldFilePath, char *pNewFilePath);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Get a file attributes.
///
/// \param pFilePath   - [in] File path
/// \param pAttributes - [out] File attributes
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileGetAttributes (char *pFilePath, OAL_FILE_ATTRIBUTES *pAttributes);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Set file attributes.
///
/// \param pFilePath   - [in] File path
/// \param pAttributes - [in] File attributes
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileSetAttributes (char *pFilePath, OAL_FILE_ATTRIBUTES *pAttributes);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Get the current working directory.
///
/// \param pDriveLetter - [in] Top level drive letter where to retrieve the current directory
/// \param pFilePath    - [out] Directory file path
///
/// \return
///    - #LIB_SUCCESS
///    - #LIB_FAILURE
/// 
///    - Currently this API is not implemented.
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileGetCurrentWorkingDirectory (char *pDriveLetter, char *pFilePath);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Set the current working directory. 
///
/// \param pFilePath - [in] Directory file path
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileSetCurrentWorkingDirectory (char *pFilePath);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Get the number of entries in a directory.
///
/// \param pFilePath - [in] Directory file path
/// \param pCount - [out] Directory entry count
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileGetDirectoryEntryCount(char *pFilePath, unsigned int *pCount);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Open directory iterator and get first directory entry.
///
/// \param pHandle  - [out] Pointer to directory iterator
/// \param pEntry   - [out] Directory entry
/// \param pPattern - [in] Directory filter pattern
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileGetFirstDirectoryEntry(OAL_DIRECTORY_HANDLE *pHandle, OAL_DIRECTORY_ENTRY  *pEntry, char *pPattern);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Get next directory entry.
///
/// \param pHandle - [in] Pointer to directory iterator
/// \param pEntry  - [out] Directory entry
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileGetNextDirectoryEntry(OAL_DIRECTORY_HANDLE *pHandle, OAL_DIRECTORY_ENTRY  *pEntry);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Closes directory iterator.
///
/// \param pHandle - [in] Pointer to directory iterator handle
///
/// \return
///    - #LIB_SUCCESS
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileDoneWithDirectory(OAL_DIRECTORY_HANDLE *pHandle);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Create a directory.
///
/// \param pFilePath - [in] Directory file path
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileCreateDirectory (char *pFilePath);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Erase a directory.
///
/// \param pFilePath - [in] Directory file path
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileEraseDirectory (char *pFilePath);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Delete a directory.
///
/// \param pFilePath - [in] Directory file path
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileDeleteDirectory (char *pFilePath);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Copy one file to another.
///
/// \param sourceFilePath - [in] Source file path
/// \param destFilePath   - [in] Destination file path
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileCopy (char *sourceFilePath, char *destFilePath);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Get file information on the specified drive.
///
/// \param pPath      - [in] Drive letter
/// \param pEntry     - [out] Directory entry
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_GetFileState(char *pPath, OAL_DIRECTORY_ENTRY  *pEntry);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Get file information on the specified drive.
///
/// \param pFileDescriptor  - [in] File Descriptor
/// \param pEntry           - [out] Directory entry
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_GetFileIDState(OAL_FILE_DESCRIPTOR *pFileDescriptor, OAL_DIRECTORY_ENTRY  *pEntry);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Set a file attributes.
///
/// \param pFileDescriptor       - [in] File Descriptor.
/// \param cmds                     - [in] Set ID file command #OAL_FILE_SET_COMMANDS
/// \param pDateTime             - [in] Pointer for file date and time structure.
/// \param attr                        - [in] Pointer for file attributes.
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_SetFileIDState(OAL_FILE_DESCRIPTOR *pFileDescriptor, int cmds, OAL_DATE_TIME* pDateTime, OAL_FILE_ATTRIBUTES *attr);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Disk flush on the specified drive.
///
/// \param pFilePath      - [in] Directory file path
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_DiskFlush(const char *pFilePath);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Change the volume label of the specified drive.
///
/// \param pDriveLetter     - [in] Disk drive letter
/// \param pNewVolumeLabel  - [in] New volume label to be changed
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH
///    - #OAL_ERR_FILE_SYSTEM
///    - #OAL_ERR_FILE_IO
///    - #OAL_ERR_FILE_ACCESS
///    - #OAL_ERR_FILE_OUT_OF_SPACE
///    - #OAL_ERR_FILE_EXISTS
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_DriveSetVolumeLabel(char *pDriveLetter, char *pNewVolumeLabel);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Get the volume label of the specified drive.
///
/// \param pDriveLetter     - [in] Disk drive letter
/// \param pNewVolumeLabel  - [out] Volume label to be set
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE             
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH   
///    - #OAL_ERR_FILE_SYSTEM         
///    - #OAL_ERR_FILE_IO             
///    - #OAL_ERR_FILE_ACCESS         
///    - #OAL_ERR_FILE_OUT_OF_SPACE   
///    - #OAL_ERR_FILE_EXISTS 
///    - #OAL_ERR_INVALID_FILE_DESCRIPTOR
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_DriveGetVolumeLabel(char *pDriveLetter, char *pNewVolumeLabel);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Delete a directory with sub dirctories and sub files. 
///
/// \param name - [in] Directory file path
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE             
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH   
///    - #OAL_ERR_FILE_SYSTEM         
///    - #OAL_ERR_FILE_IO             
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_DirDeleteRecursively(char *name);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  Erase a directory.
///
/// \param pFilePath - [in] Directory file path
///
/// \return
///    - #LIB_SUCCESS
///    - #OAL_ERR_NO_FILE             
///    - #OAL_ERR_INVALID_DRIVE_LETTER
///    - #OAL_ERR_INVALID_FILE_PATH   
///    - #OAL_ERR_FILE_SYSTEM         
///    - #OAL_ERR_FILE_IO             
///    - #LIB_FAILURE
////////////////////////////////////////////////////////////////////////
LIB_RESULT OAL_FileEraseDirectory (char *pFilePath);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
///  This function registers an application task with the file system.
///
/// Parameters:   
///
///
/// \return
///    - # LIB_SUCCESS - Operation succeeded.
///    - # LIB_FAILURE - Operation failed.
////////////////////////////////////////////////////////////////////////
LIB_RESULT FileSystemRegisterTaskWithFS(void);

////////////////////////////////////////////////////////////////////////
/// \par Descriptions:
/// This function deregisters an application task with the file system.
///
///
/// \return
///    - # LIB_SUCCESS - Operation succeeded.
///    - # LIB_FAILURE - Operation failed.
////////////////////////////////////////////////////////////////////////
LIB_RESULT FileSystemDeRegisterTaskWithFS(void);


// end of \defgroup OAL_File
/// @}
#ifdef __cplusplus
}
#endif

#endif // File Guard

