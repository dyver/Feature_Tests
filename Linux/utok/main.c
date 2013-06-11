#include <iconv.h> /* for iconv() */
#include <stdio.h>
#include <string.h> /* for strlen() */

/* Перекодирование строк */
static int convert_string(const char* from, const char* to, char* source, char* destination);
/* Для вывода на МФП */
void fromUTF8toCP1251(char* source, char* destination);
/* Для ввода из МФП */
void fromCP1251toUTF8(char* source, char* destination);
/* Для ввода из конфигурационных файлов */
void fromKOI8toUTF8(char* source, char* destination);

#define MaxBytes 80

static int convert_string(const char* from, const char* to, char* source, char* destination)
{
    size_t src_size;
    char* tmp_src;
    size_t dst_size;
    char* tmp_dst;
    iconv_t cd;
    size_t res;

    cd = iconv_open(to, from);
    if (cd == (iconv_t)(-1)) {
        printf("ERROR: UTF-8 -> KOI8-R recode don't work: no such converter\n");
        iconv_close(cd);
        return -1;
    }
    src_size = strlen(source);
    dst_size = MaxBytes;
    tmp_src = source;
    tmp_dst = destination;
    res = iconv(cd, &tmp_src, &src_size, &tmp_dst, &dst_size);
    iconv_close(cd);
    if (res == (size_t)(-1)) {
        printf("ERROR: UTF-8 -> KOI8-R recode don't work\n");
        return -1;
    } else {
        printf("Converted %d bytes\n", res);
    }
    
    return res;
}

void fromUTF8toCP1251(char* source, char* destination)
{
    convert_string("UTF8", "CP1251", source, destination);
}

void fromCP1251toUTF8(char* source, char* destination)
{
    convert_string("CP1251", "UTF8" , source, destination);
}

void fromKOI8toUTF8(char* source, char* destination)
{
    convert_string("KOI8-R", "UTF8", source, destination);
}

#include <time.h>

void end_of_time(void)
{
    {
        time_t t = 2147483648U;/*time(&t);*/
        struct tm *bt = localtime(&t);
        printf("%d\n", (int)t);
        fputs(asctime(bt), stdout);
    }

    /* Конец света */
    /* Tue Jan 19 07:14:07 2038 */
    /* Fri Dec 13 23:15:52 1901 */
}

int main(void)
{
    char src[MaxBytes];
    /*size_t src_size;*/
    /*char* tmp_src;*/
    char dst[MaxBytes];
    /*size_t dst_size;*/
    /*char* tmp_dst;*/
    /*iconv_t cd;*/
    /*size_t res;*/
    int i;

    for (i = 0; i < MaxBytes; ++i) {
        src[i] = '\0';
        dst[i] = '\0';
    }
/*
    cd = iconv_open("KOI8-R", "UTF8");
    if (cd == (iconv_t)(-1)) {
        printf("ERROR: UTF-8 -> KOI8-R recode don't work: no such converter\n");
        iconv_close(cd);
        return -1;
    }
    strcpy(src, "Входная строка в UTF-8");
    src_size = strlen(src);
    dst_size = MaxBytes;
    printf("Before: src=%s, size=%d, strlen=%d\n", src, src_size, strlen(src));
    tmp_src = src;
    tmp_dst = dst;
    res = iconv(cd, &tmp_src, &src_size, &tmp_dst, &dst_size);
    printf("After: dst=%s, size=%d, strlen=%d\n", dst, dst_size, strlen(dst));
    iconv_close(cd);
    if (res == (size_t)(-1)) {
        printf("ERROR: UTF-8 -> KOI8-R recode don't work\n");
        return -1;
    } else {
        printf("Converted %d bytes\n", res);
    }
*/
    strcpy(src, "Входная строка в UTF-8");
    fromUTF8toCP1251(src, dst);
    printf("Result: dst=%s, strlen=%d\n", dst, strlen(dst));

    return 0;
}