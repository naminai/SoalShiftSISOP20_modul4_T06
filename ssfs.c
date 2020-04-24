#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>

static const char *dirpath = "/home/donny/Documents";
static const char *kunci = "9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";
static const int key = 10;

void enkripsi(char *hasil, const char *string){
	if (strcmp(string,".") != 0 && strcmp(string,"..") != 0) {
	int i, len;
    i=0;
    char to[256]="";
    len = strlen(string);
    while(i < len){
        for(int j = 0; j < strlen(kunci) ;j++){
            if(string[i]=='/'){
                to[i]='/';
                break;
            }else if(string[i] == kunci[j]){
                j = j + key;
                if(j >= strlen(kunci)) j = j-strlen(kunci);
                    to[i] = kunci[j];
                    break;
                }
            }
            i++;
        }
        sprintf(hasil,"%s",to);
    }
}

void dekripsi(char *hasil, char *string)
{
	if (strcmp(string,".") != 0 && strcmp(string,"..") != 0) {
	int i,len;
    i=0;
    char to[256]="";
    len=strlen(string);
    while(i<len){
        int j=0;
        for(j=0;j<strlen(kunci);j++){
            if(string[i]=='/'){
                to[i]='/';
                break;
            }else if(string[i]==kunci[j]){
                j=j-key;
                if(j<0) j=j+strlen(kunci);
                    to[i]=kunci[j];
                    break;
                }
            }
            i++;
        }
        sprintf(hasil,"%s",to);
    }
}

void logging(int level, char *cmd, int count, const char *desc[]){ 
    time_t timer = time(NULL);
    struct tm buf = *localtime(&timer);
    FILE *file = fopen("/home/donny/fs.log", "a");
    if(level == 1){
        char info[100] = "INFO";
        fprintf(file, "%s::%02d%02d%02d-%02d:%02d:%02d::%s", info, buf.tm_year, buf.tm_mon, buf.tm_mday, buf.tm_hour, buf.tm_min, buf.tm_sec, cmd);
        for(int i=0; i < count; i++){
            fprintf(file, "::%s", desc[i]);
        }
        fprintf(file, "\n");
    }else if(level == 2){
        char warning[100] = "WARNING";
        fprintf(file, "%s::%02d%02d%02d-%02d:%02d:%02d::%s", warning, buf.tm_year, buf.tm_mon, buf.tm_mday, buf.tm_hour, buf.tm_min, buf.tm_sec, cmd);
        for(int i=0; i < count; i++){
            fprintf(file, "::%s", desc[i]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

static int xmp_getattr(const char *path, struct stat *stbuf){
    char fdir[300];;
    const char *desc[] = {path};
    logging(1, "GETATTR", 1, desc);

    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }


    int res;

    res = lstat(fdir, stbuf);
    if(res == -1) return -errno;

    return 0;
}

static int xmp_access(const char *path, int mask){
    char fdir[300];
    const char *desc[] = {path};
    logging(1, "ACCESS", 1, desc);

    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }

    int res;

    res = access(fdir, mask);
    if (res == -1) return -errno;

    return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, 
            off_t offset, struct fuse_file_info *fi){
    char fdir[300];
    const char *desc[] = {path};
    logging(1, "READDIR", 1, desc);

    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }

    DIR *dp;
    struct dirent *de;

    (void) offset;
    (void) fi;

    dp = opendir(fdir);
    if(dp == NULL) return -errno;

    while ((de = readdir(dp))!= NULL)
    {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        if(filler(buf, de->d_name, &st, 0)) break;
    }

    closedir(dp);
    return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi){
	char fdir[300];
	if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }
    const char *desc[] = {path};
    logging(1, "OPEN", 1, desc);
	
    int res;
	res = open(fdir, fi->flags);
	if (res == -1) return -errno;
	fi->fh = res;
    
    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi){
    char fdir[300];
    if(strcmp(path, "/") == 0){
    sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }
    const char *desc[] = {path};
    logging(1, "READ", 1, desc);

    int fd;

    if (fi == NULL)
        fd = open(fdir, O_RDONLY);
    else
        fd = fi->fh;

    if (fd == -1) 
        return -errno;
    int res = pread(fd, buf, size, offset);
    if (res == -1) 
        res = -errno;
    if (fi == NULL) 
        close(fd);
  
  return res;
}

static int xmp_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi){
    char fdir[300];
    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }
    const char *desc[] = {path};
    logging(1, "WRITE", 1, desc);

    int fd;
    int res;

    (void) fi;
    if(fi == NULL) fd = open(fdir, O_WRONLY);
    else fd = fi->fh;

    if(fd == -1) 
        return -errno;

    res = pwrite(fd, buf, size, offset);
    if(res == -1) 
        res = -errno;

    if(fi == NULL) 
        close(fd);
    return res;
}

static int xmp_truncate(const char *path, off_t size){
    char fdir[300];
    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }
    
    int res = truncate(fdir, size);
    
    if (res == -1) res = -errno;
    return res;
}

static int xmp_unlink(const char *path){
    char fdir[300];
    const char *desc[] = {path};
    logging(2, "UNLINK", 1, desc);

    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }
    

    int res;
    res = unlink(fdir);
    if(res == -1) 
        return -errno;

    return 0;
}

static int xmp_readlink(const char *path, char *buf, size_t size){
    char fdir[300];
    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }
    const char *desc[] = {path};
    logging(1, "READLINK", 1, desc);

	int res;

	res = readlink(fdir, buf, size - 1);
	if (res == -1)
		return -errno;

	buf[res] = '\0';

	return 0;
}

static int xmp_mkdir(const char *path, mode_t mode){
    char fdir[300];
    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }
    const char *desc[] = {path};
    logging(1, "MKDIR", 1, desc);

	int res;

	res = mkdir(fdir, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_rmdir(const char *path){
    char fdir[300];
    const char *desc[] = {path};
    logging(2, "RMDIR", 1, desc);
    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }

    int res;

    res = rmdir(fdir);
    if(res -- -1) 
        return -errno;

    return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid,
		     struct fuse_file_info *fi){
    char fdir[300];
    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }
    const char *desc[] = {path};
    logging(1, "CHOWN", 1, desc);

	(void) fi;
	int res;

	res = lchown(fdir, uid, gid);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chmod(const char *path, mode_t mode,
		     struct fuse_file_info *fi){
    char fdir[300];
    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }
    const char *desc[] = {path};
    logging(1, "CHMOD", 1, desc);

	(void) fi;
	int res;

	res = chmod(fdir, mode);
	if (res == -1)
		return -errno;

	return 0;
}


static int xmp_rename(const char *from, const char *to, unsigned int flags){
    char ffrom[300];
    char fto[300];
    const char *desc[] = {from, to};
    logging(1, "RENAME", 2, desc);

    if(strcmp(from, "/") == 0){
        sprintf(ffrom, "%s", dirpath);
    } else {
        sprintf(ffrom, "%s%s", dirpath, from);
    }

    if(strcmp(to, "/") == 0){
        sprintf(fto, "%s", dirpath);
    } else {
        sprintf(fto, "%s%s", dirpath, to);
    }

	int res;

	if (flags)
		return -EINVAL;

	res = rename(ffrom, fto);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_mknod(const char *path, mode_t mode, dev_t rdev){
	int res;
	char fdir[300];
    const char *desc[] = {path};
    logging(1, "MKNOD", 1, desc);
	if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }

	if (S_ISREG(mode)) {
		res = open(fdir, O_CREAT | O_EXCL | O_WRONLY, mode);
		if (res >= 0)
			res = close(res);
	} else if (S_ISFIFO(mode))
		res = mkfifo(fdir, mode);
	else
		res = mknod(fdir, mode, rdev);
	if (res == -1)
		return -errno;

	return 0;
}


static int xmp_symlink(const char *from, const char *to){
    char ffrom[300];
    char fto[300];
    const char *desc[] = {from, to};
    logging(1, "SYMLINK", 2, desc);

    if(strcmp(from, "/") == 0){
        sprintf(ffrom, "%s", dirpath);
    } else {
        sprintf(ffrom, "%s%s", dirpath, from);
    }

    if(strcmp(to, "/") == 0){
        sprintf(fto, "%s", dirpath);
    } else {
        sprintf(fto, "%s%s", dirpath, to);
    }
    int res;

	res = symlink(ffrom, fto);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_link(const char *from, const char *to){
    char ffrom[300];
    char fto[300];
    const char *desc[] = {from, to};
    logging(1, "LINK", 2, desc);

    if(strcmp(from, "/") == 0){
        sprintf(ffrom, "%s", dirpath);
    } else {
        sprintf(ffrom, "%s%s", dirpath, from);
    }

    if(strcmp(to, "/") == 0){
        sprintf(fto, "%s", dirpath);
    } else {
        sprintf(fto, "%s%s", dirpath, to);
    }

	int res;

	res = link(ffrom, fto);
	if (res == -1)
		return -errno;

	return 0;
}


static int xmp_statfs(const char *path, struct statvfs *stbuf){
	int res;
	char fdir[300];
    const char *desc[] = {path};
    logging(1, "STATFS", 1, desc);
    if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }

	res = statvfs(fdir, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2]){
	int res;
	struct timeval tv[2];
    char fdir[300];
    const char *desc[] = {path};
    logging(1, "UTIMENS", 1, desc);
	if(strcmp(path, "/") == 0){
        sprintf(fdir, "%s", dirpath);
    } else {
        sprintf(fdir, "%s%s", dirpath, path);
    }

	tv[0].tv_sec = ts[0].tv_sec;
	tv[0].tv_usec = ts[0].tv_nsec / 1000;
	tv[1].tv_sec = ts[1].tv_sec;
	tv[1].tv_usec = ts[1].tv_nsec / 1000;

	res = utimes(fdir, tv);
	if (res == -1)
		return -errno;

	return 0;
}


static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.access		= xmp_access,
	.readlink	= xmp_readlink,
	.readdir	= xmp_readdir,
	.mknod		= xmp_mknod,
	.mkdir		= xmp_mkdir,
	.symlink	= xmp_symlink,
	.unlink		= xmp_unlink,
	.rmdir		= xmp_rmdir,
	.rename		= xmp_rename,
	.link		= xmp_link,
	.chmod		= xmp_chmod,
	.chown		= xmp_chown,
	.truncate	= xmp_truncate,
	.utimens	= xmp_utimens,
	.open		= xmp_open,
	.read		= xmp_read,
	.write		= xmp_write,
	.statfs		= xmp_statfs,
};

int main(int argc, char *argv[]) 
{
  umask(0);
  return fuse_main(argc, argv, &xmp_oper, NULL);
}
