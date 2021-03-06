#ifndef WIRE_H
#define WIRE_H

class MountPointInfo {
  public:
    MountPointInfo(jobject mountPointInfo) {
      jMountPointInfo = mountPointInfo;
    }

    MountPointInfo(const MountPointInfo& s) {
      jMountPointInfo=  JniHelper::GetEnv()->NewGlobalRef(s.jMountPointInfo);
    }

    void operator = (const MountPointInfo& s) {
      jMountPointInfo=  JniHelper::GetEnv()->NewGlobalRef(s.jMountPointInfo);
    }

    ~MountPointInfo() {
      JniHelper::DeleteObjectRef(jMountPointInfo);
    }

    std::string ToString() {
        try {
          return JniHelper::CallStringMethod(jMountPointInfo, "alluxio/wire/MountPointInfo", "toString");
        } catch (std::string e ) {
          return "";
        }
    }
   private:
    jobject jMountPointInfo;
};

class URIStatus {
  public:
    URIStatus(jobject URIStatus) {
        jURIStatus = URIStatus;
    }

    URIStatus(const URIStatus& s) {
      jURIStatus=  JniHelper::GetEnv()->NewGlobalRef(s.jURIStatus);
    }

    void operator = (const URIStatus& s) {
      jURIStatus=  JniHelper::GetEnv()->NewGlobalRef(s.jURIStatus);
    }

    ~URIStatus() {
        JniHelper::DeleteObjectRef(jURIStatus);
    }

    std::string ToString() {
        try {
          return JniHelper::CallStringMethod(jURIStatus, "alluxio/client/file/URIStatus", "toString");
        } catch (std::string e ) {
          return "";
        }
    }

  private:
    jobject jURIStatus;
};

#endif // WIRE_H
