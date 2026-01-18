/**
 * @file fb_registry.c
 * @brief 功能块注册表实现
 * @version 1.0
 * @date 2026-01-18
 */

#include "fb_registry.h"
#include <stdlib.h>
#include <string.h>

/* ============================================================================
 * 静态变量
 * ========================================================================== */

static fb_registry_entry_t *g_registry_head = NULL;
static size_t g_registry_count = 0;

/* ============================================================================
 * 函数实现
 * ========================================================================== */

plcopen_error_t fb_registry_register(const fb_info_t *info)
{
    if (info == NULL || info->name == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    /* 检查是否已存在 */
    if (fb_registry_find(info->name) != NULL) {
        return PLCOPEN_ERR_ALREADY_EXISTS;  /* 已存在 */
    }

    /* 分配新条目 */
    fb_registry_entry_t *entry = (fb_registry_entry_t *)malloc(sizeof(fb_registry_entry_t));
    if (entry == NULL) {
        return PLCOPEN_ERR_OUT_OF_MEMORY;
    }

    /* 复制信息 */
    memcpy(&entry->info, info, sizeof(fb_info_t));

    /* 复制名称字符串 */
    size_t name_len = strlen(info->name) + 1;
    char *name_copy = (char *)malloc(name_len);
    if (name_copy == NULL) {
        free(entry);
        return PLCOPEN_ERR_OUT_OF_MEMORY;
    }
    memcpy(name_copy, info->name, name_len);
    entry->info.name = name_copy;

    /* 复制描述字符串 */
    if (info->description != NULL) {
        size_t desc_len = strlen(info->description) + 1;
        char *desc_copy = (char *)malloc(desc_len);
        if (desc_copy == NULL) {
            free((void *)entry->info.name);
            free(entry);
            return PLCOPEN_ERR_OUT_OF_MEMORY;
        }
        memcpy(desc_copy, info->description, desc_len);
        entry->info.description = desc_copy;
    }

    /* 添加到链表头部 */
    entry->next = g_registry_head;
    g_registry_head = entry;
    g_registry_count++;

    return PLCOPEN_OK;
}

const fb_info_t* fb_registry_find(const char *name)
{
    if (name == NULL) {
        return NULL;
    }

    fb_registry_entry_t *entry = g_registry_head;
    while (entry != NULL) {
        if (strcmp(entry->info.name, name) == 0) {
            return &entry->info;
        }
        entry = entry->next;
    }

    return NULL;
}

const fb_info_t** fb_registry_list(size_t *count)
{
    if (count != NULL) {
        *count = g_registry_count;
    }

    if (g_registry_count == 0) {
        return NULL;
    }

    /* 分配指针数组 */
    const fb_info_t **list = (const fb_info_t **)malloc(
        g_registry_count * sizeof(fb_info_t *)
    );
    if (list == NULL) {
        return NULL;
    }

    /* 填充数组 */
    fb_registry_entry_t *entry = g_registry_head;
    size_t i = 0;
    while (entry != NULL && i < g_registry_count) {
        list[i++] = &entry->info;
        entry = entry->next;
    }

    return list;
}

plcopen_error_t fb_registry_unregister(const char *name)
{
    if (name == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    fb_registry_entry_t *prev = NULL;
    fb_registry_entry_t *entry = g_registry_head;

    while (entry != NULL) {
        if (strcmp(entry->info.name, name) == 0) {
            /* 从链表中移除 */
            if (prev == NULL) {
                g_registry_head = entry->next;
            } else {
                prev->next = entry->next;
            }

            /* 释放内存 */
            free((void *)entry->info.name);
            if (entry->info.description != NULL) {
                free((void *)entry->info.description);
            }
            free(entry);

            g_registry_count--;
            return PLCOPEN_OK;
        }

        prev = entry;
        entry = entry->next;
    }

    return PLCOPEN_ERR_NOT_FOUND;  /* 未找到 */
}

void fb_registry_clear(void)
{
    fb_registry_entry_t *entry = g_registry_head;

    while (entry != NULL) {
        fb_registry_entry_t *next = entry->next;

        free((void *)entry->info.name);
        if (entry->info.description != NULL) {
            free((void *)entry->info.description);
        }
        free(entry);

        entry = next;
    }

    g_registry_head = NULL;
    g_registry_count = 0;
}

size_t fb_registry_count(void)
{
    return g_registry_count;
}
