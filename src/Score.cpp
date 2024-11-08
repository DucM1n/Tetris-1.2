// #include "Score.h"
// #include "raylib.h"
// #include "stdlib.h"
// #define STORAGE_DATA_FILE "storage.data"

// typedef enum 
//     {
//         STORAGE_POSITION_SCORE = 0,
//         STORAGE_POSITION_HIGHSCORE = 1
//     } StorageData;

//     static bool SaveStorageValue(unsigned int position, int value);
//     static int LoadStorageValue(unsigned int position);

// // Score::Score()
// // {
    
// // };
// bool SaveStorageValue(unsigned int position, int value)
// {
//     bool success = false;
//     int dataSize = 0;
//     unsigned int newDataSize = 0;
//     unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);
//     unsigned char *newFileData = NULL;

//     if (fileData != NULL)
//     {
//         if (dataSize <= (position*sizeof(int)))
//         {
//             // Increase data size up to position and store value
//             newDataSize = (position + 1)*sizeof(int);
//             newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);

//             if (newFileData != NULL)
//             {
//                 // RL_REALLOC succeded
//                 int *dataPtr = (int *)newFileData;
//                 dataPtr[position] = value;
//             }
//             else
//             {
//                 // RL_REALLOC failed
//                 TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", STORAGE_DATA_FILE, dataSize, position*sizeof(int));

//                 // We store the old size of the file
//                 newFileData = fileData;
//                 newDataSize = dataSize;
//             }
//         }
//         else
//         {
//             // Store the old size of the file
//             newFileData = fileData;
//             newDataSize = dataSize;

//             // Replace value on selected position
//             int *dataPtr = (int *)newFileData;
//             dataPtr[position] = value;
//         }

//         success = SaveFileData(STORAGE_DATA_FILE, newFileData, newDataSize);
//         RL_FREE(newFileData);

//         TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
//     }
//     else
//     {
//         TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", STORAGE_DATA_FILE);

//         dataSize = (position + 1)*sizeof(int);
//         fileData = (unsigned char *)RL_MALLOC(dataSize);
//         int *dataPtr = (int *)fileData;
//         dataPtr[position] = value;

//         success = SaveFileData(STORAGE_DATA_FILE, fileData, dataSize);
//         UnloadFileData(fileData);

//         TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
//     }

//     return success;
// }

// // Load integer value from storage file (from defined position)
// // NOTE: If requested position could not be found, value 0 is returned
// int LoadStorageValue(unsigned int position)
// {
//     int value = 0;
//     int dataSize = 0;
//     unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);

//     if (fileData != NULL)
//     {
//         if (dataSize < ((int)(position*4))) TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", STORAGE_DATA_FILE, position);
//         else
//         {
//             int *dataPtr = (int *)fileData;
//             value = dataPtr[position];
//         }

//         UnloadFileData(fileData);

//         TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", STORAGE_DATA_FILE, value);
//     }

//     return value;
// }