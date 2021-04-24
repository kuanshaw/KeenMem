#ifndef __KUAN_MEM_H
#define __KUAN_MEM_H

#define KMEM_BUFFER_SIZE        128
#define KMEM_BLOCK_SIZE         16

#define K_NULL                  0


/** 
 * @brief      内存拷贝函数
 * @param[in]  destin 内存拷贝目标
 * @param[in]  source 内存拷贝数据来源
 * @param[in]  n 拷贝字节数
 * @retval     内存拷贝目标区的指针
 * @note       
 */ 
void *k_memcpy(void *destin, const void *source, unsigned int n);


/** 
 * @brief      内存初始化函数
 * @param[in]  s 内存区域
 * @param[in]  ch 初始化字符
 * @param[in]  n 初始化字节数
 * @retval     内存区的指针
 * @note       
 */ 
void *k_memset(void *s, int ch, unsigned int n);


/** 
 * @brief      申请内存函数
 * @param[in]  size 申请字节数
 * @retval     内存区指针
 * @note       
 */ 
void *k_malloc(unsigned int size);


/** 
 * @brief      释放内存函数
 * @param[in]  ptr 要释放的内存指针
 * @retval     
 * @note       
 */ 
void k_free(void *ptr);




#endif
