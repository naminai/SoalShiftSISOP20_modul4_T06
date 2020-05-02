# SoalShiftSISOP20_modul4_T06 
Penyelesaian Soal Shift Modul 4 Sistem Operasi 2020 
Kelompok T06 
  * Donny Kurnia Ramadhani (05311840000004) 
  * Made Krisnanda Utama (0531184000033) 

--- 
## Daftar Isi 
* [SSFS](#ssfs)
  * [Soal](#soal)
  * [Source Code](#code)
  * [soal 4](#soal-4)
* [Kendala Praktikkan](#kendala)
--- 
## SSFS
Source Code : [source](https://github.com/naminai/SoalShiftSISOP20_modul4_T06/tree/master)
### Soal
Di suatu perusahaan, terdapat pekerja baru yang super jenius, ia bernama jasir. Jasir baru bekerja selama seminggu di perusahan itu, dalam waktu seminggu tersebut ia selalu terhantui oleh ketidak amanan dan ketidak efisienan file system yang digunakan perusahaan tersebut. Sehingga ia merancang sebuah file system yang sangat aman dan efisien. Pada segi keamanan, Jasir telah menemukan 2 buah metode enkripsi file. Pada mode enkripsi pertama, nama file-file pada direktori terenkripsi akan dienkripsi menggunakan metode substitusi. Sedangkan pada metode enkripsi yang kedua, file-file pada direktori terenkripsi akan di-split menjadi file-file kecil. Sehingga orang-orang yang tidak menggunakan filesystem rancangannya akan kebingungan saat mengakses direktori terenkripsi tersebut. Untuk segi efisiensi, dikarenakan pada perusahaan tersebut sering dilaksanakan sinkronisasi antara 2 direktori, maka jasir telah merumuskan sebuah metode agar filesystem-nya mampu mengsingkronkan kedua direktori tersebut secara otomatis. Agar integritas filesystem tersebut lebih terjamin, maka setiap command yang dilakukan akan dicatat kedalam sebuah file log.
(catatan: filesystem berfungsi normal layaknya linux pada umumnya)
(catatan: mount source (root) filesystem adalah direktori /home/[user]/Documents)

Berikut adalah detail filesystem rancangan jasir:
1. Enkripsi versi 1:
Jika sebuah direktori dibuat dengan awalan “encv1_”, maka direktori tersebut akan menjadi direktori terenkripsi menggunakan metode enkripsi v1.
Jika sebuah direktori di-rename dengan awalan “encv1_”, maka direktori tersebut akan menjadi direktori terenkripsi menggunakan metode enkripsi v1.
Apabila sebuah direktori terenkripsi di-rename menjadi tidak terenkripsi, maka isi adirektori tersebut akan terdekrip.
Setiap pembuatan direktori terenkripsi baru (mkdir ataupun rename) akan tercatat ke sebuah database/log berupa file.
Semua file yang berada dalam direktori ter enkripsi menggunakan caesar cipher dengan key.
```
9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO
```
Misal kan ada file bernama “kelincilucu.jpg” dalam directory FOTO_PENTING, dan key yang dipakai adalah 10
“encv1_rahasia/FOTO_PENTING/kelincilucu.jpg” => “encv1_rahasia/ULlL@u]AlZA(/g7D.|_.Da_a.jpg
Note : Dalam penamaan file ‘/’ diabaikan, dan ekstensi tidak perlu di encrypt.
Metode enkripsi pada suatu direktori juga berlaku kedalam direktori lainnya yang ada didalamnya.
2. Enkripsi versi 2:
Jika sebuah direktori dibuat dengan awalan “encv2_”, maka direktori tersebut akan menjadi direktori terenkripsi menggunakan metode enkripsi v2.
Jika sebuah direktori di-rename dengan awalan “encv2_”, maka direktori tersebut akan menjadi direktori terenkripsi menggunakan metode enkripsi v2.
Apabila sebuah direktori terenkripsi di-rename menjadi tidak terenkripsi, maka isi direktori tersebut akan terdekrip.
Setiap pembuatan direktori terenkripsi baru (mkdir ataupun rename) akan tercatat ke sebuah database/log berupa file.
Pada enkripsi v2, file-file pada direktori asli akan menjadi bagian-bagian kecil sebesar 1024 bytes dan menjadi normal ketika diakses melalui filesystem rancangan jasir. Sebagai contoh, file File_Contoh.txt berukuran 5 kB pada direktori asli akan menjadi 5 file kecil yakni: File_Contoh.txt.000, File_Contoh.txt.001, File_Contoh.txt.002, File_Contoh.txt.003, dan File_Contoh.txt.004.
Metode enkripsi pada suatu direktori juga berlaku kedalam direktori lain yang ada didalam direktori tersebut (rekursif).

3. Sinkronisasi direktori otomatis:

Tanpa mengurangi keumuman, misalkan suatu directory bernama dir akan tersinkronisasi dengan directory yang memiliki nama yang sama dengan awalan sync_ yaitu sync_dir. Persyaratan untuk sinkronisasi yaitu:
Kedua directory memiliki parent directory yang sama.
Kedua directory kosong atau memiliki isi yang sama. Dua directory dapat dikatakan memiliki isi yang sama jika memenuhi:
Nama dari setiap berkas di dalamnya sama.
Modified time dari setiap berkas di dalamnya tidak berselisih lebih dari 0.1 detik.
Sinkronisasi dilakukan ke seluruh isi dari kedua directory tersebut, tidak hanya di satu child directory saja.
Sinkronisasi mencakup pembuatan berkas/directory, penghapusan berkas/directory, dan pengubahan berkas/directory.

Jika persyaratan di atas terlanggar, maka kedua directory tersebut tidak akan tersinkronisasi lagi.
Implementasi dilarang menggunakan symbolic links dan thread.

4. Log system:

Sebuah berkas nantinya akan terbentuk bernama "fs.log" di direktori *home* pengguna (/home/[user]/fs.log) yang berguna menyimpan daftar perintah system call yang telah dijalankan.
Agar nantinya pencatatan lebih rapi dan terstruktur, log akan dibagi menjadi beberapa level yaitu INFO dan WARNING.
Untuk log level WARNING, merupakan pencatatan log untuk syscall rmdir dan unlink.
Sisanya, akan dicatat dengan level INFO.
Format untuk logging yaitu:
```
[LEVEL]::[yy][mm][dd]-[HH]:[MM]:[SS]::[CMD]::[DESC ...]
```
```
LEVEL    : Level logging
yy        : Tahun dua digit
mm         : Bulan dua digit
dd         : Hari dua digit
HH         : Jam dua digit
MM         : Menit dua digit
SS         : Detik dua digit
CMD          : System call yang terpanggil
DESC      : Deskripsi tambahan (bisa lebih dari satu, dipisahkan dengan ::)
```
Contoh format logging nantinya seperti:
```
INFO::200419-18:29:28::MKDIR::/iz1
INFO::200419-18:29:33::CREAT::/iz1/yena.jpg
INFO::200419-18:29:33::RENAME::/iz1/yena.jpg::/iz1/yena.jpeg
```
---
### Source Code SSFS
```
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
```
Untuk `dirpath` mengubah mount path direktori dan untuk kunci serta key digunakan untuk enkripsi dan dekripsi.
```
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
```
Digunakan untuk enkripsi V1 (belum selesai jadi nggak usah)
```
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
```
DIgunakan untuk dekripsi V1 (belum selesai jadi nggak usah)
```
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
```
Digunakan untuk Soal 4, bisa dilihat dibawah.
```
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
```
Untuk mendapatkan attribut informasi dari file atau direktori. 
```
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
```
Digunakan untuk menentukan access ke sebuah direktori atau file.
```
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
```
Untuk membaca dan membuka stream sebuah direktori.
```
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
```
Untuk membuka sebuah file.
```
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
```
Untuk membaca sebuah isi file atau direktori.
```
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
```
Untuk melakukan writing kepada file atau direktori.
```
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
```
Untuk melakukan truncate data kepada sebuah file atau direktori.
```
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
```
Untuk melakukan unlink dalam penghapusan file.
```
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
```
Untuk membaca link baru ketika kita membuat sebuah file baru.
```
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
```
Digunakan untuk membuat direktori baru.
```
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
```
Digunakan untuk menghapus direktori.
```
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
```
Digunakan untuk mengimplementasikan command `chown` pada FUSE.
```
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
```
Digunakan untuk mengimplementasikan command `chmod` pada FUSE.
```
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
```
Digunakan untuk melakukan proses rename pada sebuah file atau direktori.
```
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
```
Tidka terlalu sering digunakan, tapi digunakan untuk mengetahui permission dari file.
```

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
```
Membuat sebuah symbolic link.
```
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
```
Digunakan untuk membuat link pada file.
```
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
```
Digunakan untuk melakukan stat pada filesystem.
```
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
```
Untuk mengetahui user time environment dan mengimplementasikannya kepada FUSE. Penting untuk pembuatan dan penghapusan file serta manipulasi file dan direktori, misalnya `mv`.
```
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
```
Mendeklarasikan ulang ke dalam struct `fuse_operations xmp_oper` 
```
int main(int argc, char *argv[]) 
{
  umask(0);
  return fuse_main(argc, argv, &xmp_oper, NULL);
}
```
Main program FUSE.

### Soal 4
```
void logging(int level, char *cmd, int count, const char *desc[]){
```
Deklarasi function logging dan parameter. 
`int level` digunakan untuk menentukan level command dan inputnya hanya boleh 1 atau 2, 1 untuk menandakan level INFO dan 2 untuk WARNING.
`char *cmd` digunakan untuk mengetahui command apa yang akan dilogging ke dalam `log.fs`.
`int count` digunakan untuk mengetahui berapa banyak isi desc.
`const char* desc[]` digunakan untuk mendapatkan path dari direktori atau file. Bisa lebih dari 1. 
```
    time_t timer = time(NULL);
    struct tm buf = *localtime(&timer);
```
Digunakan untuk mendapatkan waktu dibuatnya direktori atau file, lalu ditampung di struct `buf`.
```
    FILE *file = fopen("/home/donny/fs.log", "a");
```
Membuat file baru atau membuka file bernama `fs.log` pada `/home/donny` dengan mode append.
```
    if(level == 1){
        char info[100] = "INFO";
        fprintf(file, "%s::%02d%02d%02d-%02d:%02d:%02d::%s", info, buf.tm_year, buf.tm_mon, buf.tm_mday, buf.tm_hour, buf.tm_min, buf.tm_sec, cmd);
        for(int i=0; i < count; i++){
            fprintf(file, "::%s", desc[i]);
        }
        fprintf(file, "\n");
```
Jika level command merupakan INFO (semua kecuali command `unlink` dan `rmdir`). Maka kita melakukan log seperti diatas.
Kita memasukkan pada log.fs menggunakan `fprintf` dengan format `"%s::%02d%02d%02d-%02d:%02d:%02d::%s", info, buf.tm_year, buf.tm_mon, buf.tm_mday, buf.tm_hour, buf.tm_min, buf.tm_sec, cmd`.
Kemudian kita melihat berapa count yang ada untuk path file.
```
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
```
Jika level command merupakan WARNING (untuk command `unlink` dan `rmdir`). Maka kita melakukan log seperti diatas.
Kita memasukkan pada log.fs menggunakan `fprintf` dengan format `"%s::%02d%02d%02d-%02d:%02d:%02d::%s", info, buf.tm_year, buf.tm_mon, buf.tm_mday, buf.tm_hour, buf.tm_min, buf.tm_sec, cmd`.
Kemudian kita melihat berapa count yang ada untuk path file.

### Output Soal 4.
![Modul 4 soal 4](https://user-images.githubusercontent.com/61267430/79032180-a9c59880-7bce-11ea-93b4-9f01ba9f6cd0.png

---
## Kendala
1. Soal terlalu kompleks untuk pemahaman kelompok kami yang sederhana 
2. Soal 1, 2, dan 3 kurang bisa dipahami secara jelas, sehingga tidak terselesaikan sama sekali.
