#include "kmem.h"

#define _BLOCK_NO_USE       0
#define _BLOCK_NUM          (KMEM_BUFFER_SIZE / KMEM_BLOCK_SIZE)

static void _buff_init(void);
static char _buff_alloc(unsigned int allocsize, unsigned int *buffpos);
static char _buff_free(unsigned int buffpos);

static unsigned char _membuff[KMEM_BUFFER_SIZE] = {0};
static unsigned int _blk_state[_BLOCK_NUM] = {0};
static char _init_flag = 0;


/** 
 * @brief      内存拷贝函数
 * @param[in]  destin 内存拷贝目标
 * @param[in]  source 内存拷贝数据来源
 * @param[in]  n 拷贝字节数
 * @retval     内存拷贝目标区的指针
 * @note       
 */ 
void *k_memcpy(void *destin, const void *source, unsigned int n)
{  
    char *dst_ptr = (char *)destin;
    char *src_ptr = (char *)source;

    while (n--)
        *dst_ptr++ = *src_ptr++;

    return destin;
}  


/** 
 * @brief      内存初始化函数
 * @param[in]  s 内存区域
 * @param[in]  ch 初始化字符
 * @param[in]  n 初始化字节数
 * @retval     内存区的指针
 * @note       
 */ 
void *k_memset(void *s, int ch, unsigned int n)
{
    char *m = (char *)s;
    char _ch = (char)(ch & 0xff);
    
    while (n--)
        *m++ = _ch;
    
    return s;
}


/** 
 * @brief      申请内存函数
 * @param[in]  size 申请字节数
 * @retval     内存区指针
 * @note       
 */ 
void *k_malloc(unsigned int size)
{
    unsigned int buffpos = 0;

    if(_buff_alloc(size, &buffpos))
        return K_NULL;

    return (void *)(&_membuff[buffpos]);
}


/** 
 * @brief      释放内存函数
 * @param[in]  ptr 要释放的内存指针
 * @retval     
 * @note       
 */ 
void k_free(void *ptr)
{
    unsigned int buffpos = 0;   

    buffpos = (unsigned int)ptr - (unsigned int)_membuff;

    if (buffpos < KMEM_BUFFER_SIZE)
        _buff_free(buffpos);

    return;
}


/** 
 * @brief      内存区初始化
 * @retval     
 * @note       
 */ 
static void _buff_init(void)
{  
    k_memset(_membuff, 0, KMEM_BUFFER_SIZE);
    k_memset(_blk_state, 0, _BLOCK_NUM * 2);
    _init_flag = 1;
}  


/** 
 * @brief      数组分配函数
 * @param[in]  allocsize 要申请的字节数
 * @param[out] buffpos 数组的位置
 * @retval     0-成功
 * @note       
 */ 
static char _buff_alloc(unsigned int allocsize, unsigned int *buffpos)
{
    unsigned short blk_num = 0, blk_continue_cnt= 0;
    unsigned short i = 0, j = 0;

    if (!_init_flag)
        _buff_init();

    //TODO: Calculate Block number
    blk_num = (allocsize + KMEM_BLOCK_SIZE - 1) / KMEM_BLOCK_SIZE;

    //TODO: find continue block
    for (i = (_BLOCK_NUM - 1); i >= 0 ; i--)
    {     
        if (_blk_state[i] == _BLOCK_NO_USE)   //block isn't in used
            blk_continue_cnt++;
        else 
            blk_continue_cnt = 0;   //found again

        //TODO: found! 
        if (blk_continue_cnt == blk_num)
            break;
    }

    if (blk_continue_cnt != blk_num)
        return -1;

    //TODO
    for (j = 0; j < blk_num; j++)
    {  
        _blk_state[i + j] = (blk_num - j);    //record block num
    }            

    *buffpos = i * KMEM_BLOCK_SIZE;

    return 0;
}  


/** 
 * @brief      数组释放函数
 * @param[in]  buffpos 要释放数据的位置
 * @retval     0-成功
 * @note       
 */ 
static char _buff_free(unsigned int buffpos)  
{
    unsigned short i = 0, blkpos = 0, blknum = 0;

    blkpos = buffpos / KMEM_BLOCK_SIZE;
    blknum = _blk_state[blkpos];

    //TODO: Set Block Free State
    for (i = 0; i < blknum; i++) 
    {
        _blk_state[blkpos + i] = _BLOCK_NO_USE;
    }

    return 0;  
}  


