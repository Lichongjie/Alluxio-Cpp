#include "FileSystem.h"

#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <functional>
#include <thread>

#include "JNIHelper.h"

using namespace alluxio;

void CreateDirectoryTest(FileSystem* fileSystem, const char* dirPath) {
  std::cout << "TEST - CREATE DIRECTORY: " << std::endl;
  Status status = fileSystem->CreateDirectory(dirPath);
  if (status.ok()) {
    std::cout << "SUCCESS - Created alluxio dir " << dirPath << std::endl;
  } else {
    std::cout << "FAILED - Created alluxio dir " << dirPath <<
        "REASION: " << status.ToString() << std::endl;
  }
}

void CreateFileTest(FileSystem* fileSystem, const char* path) {
  std::cout << "TEST - CREATE FILE: " << std::endl;
  FileOutStream* outStream;
  Status status = fileSystem->CreateFile(path, &outStream);
  if (status.ok()) {
    std::cout << "SUCCESS - Created alluxio file " << path << std::endl;
  } else {
    std::cout << "FAILED - Created alluxio file " << path <<
        "REASION: " << status.ToString() << std::endl;
  }
}

void DeletePathTest(FileSystem* fileSystem, const char* path) {
  std::cout << "TEST - DELETE PATH: " << std::endl;
  Status status = fileSystem->DeletePath(path);
  if (status.ok()) {
    std::cout << "SUCCESS - delete alluxio path " << path << std::endl;
  } else {
    std::cout << "FAILED - delete alluxio path " << path << "; REASION: " <<
        status.ToString() << std::endl;
  }
}

void ExistTest(FileSystem* fileSystem, const char* path) {
  std::cout << "TEST -  EXIST: " << std::endl ;
  bool* res;
  Status status = fileSystem->Exists(path, res);
  if (status.ok()) {
    std::cout << "SUCCESS -  exist  " << path << std::endl;
  } else {
    std::cout << "FAILED -  exist " << path << "; REASION: " <<
        status.ToString() << std::endl;
  }
}

void OpenFileTest(FileSystem* fileSystem, const char* path) {
  std::cout << "TEST -  OPEN FILE: " << std::endl ;
  FileInStream* inStream;
  Status status = fileSystem->OpenFile(path,  &inStream);
  if (status.ok()) {
    std::cout << "SUCCESS -  open file  " << path << std::endl;
  } else {
    std::cout << "FAILED -  open file " << path << ";  REASION: " <<
        status.ToString() << std::endl;
  }
}

void FreeTest(FileSystem* fileSystem, const char* path) {
  std::cout << "TEST -  FREE: " << std::endl;
  Status status = fileSystem->Free(path);
  if (status.ok()) {
    std::cout << "SUCCESS -  free  " << path << std::endl;
  } else {
    std::cout << "FAILED -  free " << path << ";  REASION: " <<
        status.ToString() << std::endl;
  }
}

void GetStatusTest(FileSystem* fileSystem, const char* path) {
  URIStatus* result;
  std::cout << "TEST -  GET STATUS: " << std::endl;
  Status status = fileSystem->GetStatus(path, result);
  if (status.ok()) {
    std::cout << "SUCCESS -  GET STATUS  " << path << std::endl;
  } else {
    std::cout << "FAILED - GET STATUS " << path << ";  REASION: " <<
        status.ToString() << std::endl;
  }
}

void ListStatusTest(FileSystem* fileSystem, const char* path) {
  std::vector<URIStatus> result;
  std::cout << "TEST -  LIST STATUS: " << std::endl;
  Status status = fileSystem->ListStatus(path, &result);
  if (status.ok()) {
    std::cout << "SUCCESS -  LIST STATUS  " << path << std::endl;
    for (int i = 0 ; i < result.size(); i ++) {
      std::cout << result[i].ToString() << std::endl;
    }
  } else {
    std::cout << "FAILED -  LIST STATUS " << path << ";  REASION: " <<
        status.ToString() << std::endl;
  }
}

void MountTest(FileSystem* fileSystem, const char* srcPath,
               const char* dirPath) {
  std::cout << "TEST -  MOUNT: " << std::endl;
  Status status = fileSystem->mount(srcPath, dirPath);
  if (status.ok()) {
    std::cout << "SUCCESS -  mount  " << dirPath << std::endl;
  } else {
    std::cout << "FAILED -  mount " << dirPath << ";  REASION: " <<
        status.ToString() << std::endl;
  }
}

void UnmountTest(FileSystem* fileSystem, const char* path) {
  std::cout  << "TEST -  UNMOUNT: " << std::endl;
  Status status = fileSystem->Unmount(path);
  if (status.ok()) {
    std::cout << "SUCCESS -  unmount  " << path << std::endl;
  } else {
    std::cout << "FAILED -  unmount " << path << ";  REASION: " <<
        status.ToString() << std::endl;
  }
}

void GetMountTableTest(FileSystem* fileSystem) {
  std::cout << "TEST -  GET MOUNTTABLE: " << std::endl;
  std::map<std::string, MountPointInfo> result;
  Status status = fileSystem->GetMountTable(&result);
  if (status.ok()) {
    std::cout << "SUCCESS -  GET MOUNTTABLE  " << std::endl;
    std::map<std::string, MountPointInfo>::iterator it;
  for (it = result.begin(); it != result.end();
      it ++) {
      std::string key = (std::string)it->first;
      MountPointInfo value = (MountPointInfo)it->second;
      std::cout << "key: " << key << std::endl;;
      std::cout <<  "value" << value.ToString() << std::endl;
  }
  } else {
    std::cout << "FAILED -  GET MOUNTTABLE " << ";  REASION: " <<
        status.ToString() << std::endl;
  }
}

void RenameTest(FileSystem* fileSystem, const char* srcPath,
                const char* dirPath) {
  std::cout  << "TEST -  RENAME: " << std::endl;
  Status status = fileSystem->Rename(srcPath, dirPath);
  if (status.ok()) {
    std::cout << "SUCCESS -  rename  " << srcPath << std::endl;
  } else {
    std::cout << "FAILED -  rename " << srcPath << ";  REASION: " <<
        status.ToString() << std::endl;
  }
}

void SetAttributeTest(FileSystem* fileSystem, const char* path)  {
  std::cout  << "TEST -  SET ATTRIBUTE: " << std::endl;
  Status status = fileSystem->SetAttribute(path);
  if (status.ok()) {
    std::cout << "SUCCESS -  SET ATTRIBUTE  " << path << std::endl;
  } else {
    std::cout << "FAILED -  SET ATTRIBUTE " << path << ";  REASION: " <<
        status.ToString() << std::endl;
  }
}

int main(void) {
   FileSystem* fileSystem = new FileSystem();
GetMountTableTest(fileSystem);
   return 0;
}
