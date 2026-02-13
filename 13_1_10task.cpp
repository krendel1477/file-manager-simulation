#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "os_file.h"


typedef struct Node 
{
    Node *parent;
    Node **child;
    int is_dir;
    int child_cnt;
    int size;
    char *name;
    char *full_path;
}Node;

Node *ROOT = NULL;
Node *CUR_DIR = NULL;
int FM_SIZE = 0;
int FM_OCP = 0;

int my_create (int disk_size);
int check_child (char *token, Node **node);
int my_remove(char *path, int recursive);
int remove_rec (Node *node);
int my_create_dir(const char* path);
int my_create_file(const char* path, int file_size);
int my_destroy();
int size(char *path);
int size_node_rec (Node *node, int ret_size);
void get_cur_dir(char *destiny);
void setup_file_manager(file_manager_t *fm);
int my_change_cur_dir(const char* path);

int check_child (char *token, Node **node)
{
    if(*node == NULL)
    {
        return -1;
    }
    for (int i = 0; i < (*node)->child_cnt; i++)
    {
        if(strcmp((*node)->child[i]->name, token) == 0)
        {
            (*node) = (*node)->child[i];
            return i;
        }
    }
    return -1;
}
int my_change_cur_dir(const char* path)
{
    Node *node = NULL;

    int is_find = 1;

    if(path[0] == '/') 
    {
        node = ROOT;
    }
    else 
    {
        node = CUR_DIR;
    }

    char *token, *delim_path, *free_delim;
    
    free_delim = delim_path = strdup(path);

    while ((token = strsep(&delim_path, "/")) != NULL)
    {
        if(!strcmp(token, ".") || strlen(token) <= 0
            || !strcmp(token, "") || token[0] == '\0') continue;
        
        if(!strcmp(token, ".."))
        {
            if(node->parent)
            {
                node = node->parent;
            }  
            continue;
        }
        if(check_child(token, &node) == -1)
        {
            free(free_delim);
            return 0;
        } 
    }
    if(node->is_dir == 1)
    {
        CUR_DIR = node;
        free(free_delim);
        return 1;
    }
    free(free_delim);
    return 0;
}

int my_create (int disk_size)
{
    if (ROOT != NULL || disk_size <= 0)
    {
        return 0;
    }
    FM_SIZE = disk_size;
    ROOT = (Node*)malloc(sizeof(Node));

    ROOT->parent = NULL;
    ROOT->child = NULL;
    ROOT->is_dir = 1;
    ROOT->child_cnt = 0;
    ROOT->size = 0;
    ROOT->name = strdup("/");
    ROOT->full_path = strdup("/");
    
    CUR_DIR = ROOT;
    return 1;
}

int create_node (char *path, int is_flag, int new_size)
{
    Node *runner = NULL;
    if(FM_SIZE - new_size < 0)
    {
        return 0;
    }
    if(path[0] == '/')
    {
        runner = ROOT;
    }
    else
    {
        runner = CUR_DIR;
    }
    char *token;
    char *delim_path;
    char *free_delim;
    free_delim = delim_path = strdup(path);
    while ((token = strsep(&delim_path, "/")) != NULL)
    {
        if(strcmp(token, ".") == 0 || strlen(token) <= 0 || strcmp(token, "") == 0 
        || token[0] == '\0' || check_child(token, &runner) >= 0)
            continue;
        if (strcmp(token, "..") == 0)
        {
            if(runner->parent != NULL)
            {
                runner = runner->parent;
            }
            continue;
        }
        if(runner->is_dir == 0)
        {
            free(free_delim);
            return 0;    
        }
        if(delim_path != NULL)
        {
            free(free_delim);
            return 0;
        }
        
        Node *chado = (Node*)malloc(sizeof(Node));

        chado->parent = runner;
        chado->child = NULL;
        chado->child_cnt = 0;
        chado->is_dir = is_flag;
        chado->size = new_size;
        chado->name = strdup(token);
        chado->full_path = (char*)calloc(sizeof(char), 
                            strlen(runner->full_path) + strlen(token) + strlen("/") + 1);
        strcat(chado->full_path, runner->full_path);
        strcat(chado->full_path, token);
        strcat(chado->full_path, "/");

        runner->child_cnt++;
        if(runner->child == NULL)
        {
            runner->child = (Node**)malloc(sizeof(Node*));
        }
        else
        {
            runner->child = (Node**)realloc(runner->child, sizeof(Node*)*runner->child_cnt);
        }
        runner->child[runner->child_cnt - 1] = chado;
        FM_SIZE -= new_size;
        free(free_delim);
        return 1;
    }
    free(free_delim);
    return 0;
}

int my_create_dir(const char* path)
{ 
    return create_node((char*)path, 1, 0);
}

int my_create_file(const char* path, int file_size)
{
    return create_node((char*)path, 0, file_size);
}

int remove_rec (Node *node)
{
    if(!node) return 0;
    for(int i = 0; i < node->child_cnt; ++i)
    {
        remove_rec(node->child[i]);
        node->child[i] = NULL;
    }
    FM_SIZE += node->size;
    free(node->name);
    free(node->full_path);
    free(node->child);
    free(node);
    node = NULL;
    return 1;
}

int my_remove(const char *path, int recursive)
{
    Node *node_remove = NULL;
    if(path[0] == '/')
    {
        node_remove = ROOT;
    }
    else
    {
        node_remove = CUR_DIR;
    }

    char *token;
    char *delim_path;
    char *free_delim;

    free_delim = delim_path = strdup(path);
    int rm_index = -1;
    while((token = strsep(&delim_path, "/")) != NULL)
    {
        if(strcmp(token, ".") == 0 || strlen(token) <= 0 || strcmp(token, "") == 0 
            || token[0] == '\0')
            continue;
        if (strcmp(token, "..") == 0)
        {
            if(node_remove->parent != NULL)
            {
                node_remove = node_remove->parent;
            }
            continue;
        }
        rm_index = check_child(token, &node_remove);
        if(rm_index == -1)
        {
            free(free_delim);
            return 0;
        }
    }

    if(recursive == 0 && node_remove->child_cnt > 0 && node_remove->is_dir == 1)
    {
        free(free_delim);
        return 0;
    }
    if((strcmp(CUR_DIR->full_path, node_remove->full_path)) == 0)
    {
        free(free_delim);
        return 0;
    }

    Node *node_remove_parent = node_remove->parent;
    remove_rec(node_remove);

    free(free_delim);

    node_remove_parent->child[rm_index] = NULL; 
    for(int i = rm_index; i < node_remove_parent->child_cnt - 1; ++i)
    {
        Node *tmp = node_remove_parent->child[i];
        node_remove_parent->child[i] = node_remove_parent->child[i + 1];
        node_remove_parent->child[i + 1] = tmp;
    }

    node_remove_parent->child_cnt--;
    if(node_remove_parent->child_cnt == 0){
        free(node_remove_parent->child);
        node_remove_parent->child = NULL;
        return 1;
    }    
    node_remove_parent->child = (Node**)realloc(node_remove_parent->child, sizeof(Node*)*node_remove_parent->child_cnt);
    
    return 1;
}

int my_destroy()
{
    if (ROOT == NULL)
    {
        return 0;
    }
    remove_rec(ROOT);
    ROOT = NULL;
    CUR_DIR = NULL;
    FM_SIZE = 0;
    FM_OCP = 0;
    return 1;
}

int size_node_rec (Node *node, int *ret_size)
{
    if(node == NULL)
    {
        return 0;
    }
    for (int i = 0; i < node->child_cnt; i++)
    {
        size_node_rec(node->child[i], ret_size);
    }
    *ret_size += node->size;
    return *ret_size;
}

int my_size(const char *path)
{
    Node *node = NULL;

    if(path[0] == '/') 
    {
        node = ROOT;
    }
    else 
    {
        node = CUR_DIR;
    }

    char *token, *delim_path, *free_delim;
    
    free_delim = delim_path = strdup(path);

    while ((token = strsep(&delim_path, "/")) != NULL)
    {
        if(!strcmp(token, ".") || strlen(token) <= 0 
            || !strcmp(token, "") || token[0] == '\0') continue;
        
        if(!strcmp(token, ".."))
        {
            if(node->parent) 
            {
                node = node->parent;
            }
            continue;
        }
        if(check_child(token, &node) == -1)
        {
            free(free_delim);
            return -1;
        }
    }
    free(free_delim);
    int rsize = 0;
    return size_node_rec(node, &rsize);
}

void my_get_cur_dir(char *destiny)
{
    if(ROOT != NULL)
    {
        strcpy(destiny, CUR_DIR->full_path);
    } 
    return;
}

void setup_file_manager(file_manager_t *fm)
{
    fm->create = my_create;
    fm->create_dir = my_create_dir;
    fm->create_file = my_create_file;
    fm->change_dir = my_change_cur_dir;
    fm->get_cur_dir = my_get_cur_dir;
    fm->remove = my_remove;
    fm->size = my_size;
    fm->destroy = my_destroy;
}