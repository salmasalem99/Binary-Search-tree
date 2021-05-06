#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include<string.h>

 typedef struct
 {
     struct BSTNode *left;
     struct BSTNode *right;
     char word[40];
 }BSTNode;

 BSTNode *newBSTNode(char string[40])
 {
	 BSTNode *node =(BSTNode*)malloc(sizeof(BSTNode));
     strcpy(node->word,string);
	 node->left = node->right = NULL;
	 return node;
 }

 int isEmpty(BSTNode *root)
 {
    return root == NULL? 1:0;
 }

 int size(BSTNode *root)
 {
    return (root == NULL) ? 0 :
    1 + size(root->left) + size(root->right);
 }

int max(int a, int b)
 {
    return a>b? a : b;
 }

 int height(BSTNode *root)
 {
    return (root == NULL) ? -1 : 1+max(height(root->left),height(root->right));
 }

 BSTNode* insert(BSTNode *p, char d[40])
 {
			if (p == NULL)
            {
                p = newBSTNode(d);
            }

			else if (strcmp( p->word, d)>0)
            {
                p->left = insert(p->left, d);
            }

			else if (strcmp(p->word, d)<0)
            {
                p->right = insert(p->right, d);
            }
			return p;
 }


 BSTNode* savetofile(char filename[40])
 {
    FILE* f = fopen(filename,"r");
    char word[40];
    BSTNode* root=NULL;
    while (!feof(f))
    {
        fscanf(f,"%s ",word);
        root=insert(root,word);
    }
    return root;
 }


 int inordertraversal(BSTNode *root, char word[40])
 {

    while(root!=NULL)
    {
        if(strcmp(word,root->word)==0)
            return 1;
        else if(strcmp(word,root->word)<0)
            root = root->left;
        else if(strcmp(word,root->word)>0)
            root = root->right;
    }
    return 0;
 }
 BSTNode* getlastcontent(BSTNode *root, char word[40])
 {
    BSTNode* pointer;
    while(root!=NULL)
    {
        pointer= root;
        if(strcmp(word,root->word)<0)
            root = root->left;
        else if(strcmp(word,root->word)>0)
            root = root->right;
    }
    return pointer;
  }

  BSTNode* min(BSTNode *root)
 {
			assert(root != NULL);
			BSTNode *p = root;
			while (p->left != NULL)
				p = p->left;
			return p;
 }
int determine(BSTNode* root, BSTNode* node)
{
    int flag=0;
    while(root!=node)
    {
       if(strcmp(node->word,root->word)<0)
       {
           root = root->left;
           flag=1;
       }

        else if(strcmp(node->word,root->word)>0)
        {
            root = root->right;
            flag =0;
        }
    }
    return flag;

}
BSTNode* getsuccessor(BSTNode* root, BSTNode* node)
 {
     if(node->right!=NULL)
     {
         BSTNode* temp = node->right;
         while(temp->left!=NULL) temp = temp->left;
         return temp;
     }
     else if(determine(root,node)==0 && node->right==NULL)
     {
         BSTNode* successor = NULL;
         BSTNode* ancestor = root;
         while(ancestor!=node)
         {
           if(strcmp(node->word,ancestor->word)<0)
           {
               successor = ancestor;
               ancestor = ancestor->left;
           }
           else
            ancestor=ancestor->right;
         }
         return successor;
     }
     else if(determine(root,node)==1 && node->right==NULL)
     {
         BSTNode* successor = NULL;
         BSTNode* ancestor = root;
         while(ancestor!=node)
         {
         successor = ancestor;
           if(strcmp(node->word,ancestor->word)<0)
           {
               ancestor = ancestor->left;
           }
           else
            ancestor=ancestor->right;
         }
         return successor;
     }
 }
 BSTNode* getpredeccessor(BSTNode* root, BSTNode* node)
 {
     if(node->left!=NULL)
     {
         BSTNode* temp = node->left;
         while(temp->right!=NULL) temp = temp->right;
         return temp;
     }
     else if(determine(root,node)==1 && node->left==NULL)
     {
         BSTNode* predeccessor = NULL;
         BSTNode* ancestor = root;
         while(ancestor!=node)
         {
           if(strcmp(node->word,ancestor->word)<0)
           {

               ancestor = ancestor->left;
           }
           else
           {
               predeccessor = ancestor;
               ancestor=ancestor->right;
           }

         }
         return predeccessor;
     }
     else if(determine(root,node)==0 && node->left==NULL)
     {
         BSTNode* predeccessor = NULL;
         BSTNode* ancestor = root;
         while(ancestor!=node)
         {
         predeccessor = ancestor;
           if(strcmp(node->word,ancestor->word)<0)
           {
               ancestor = ancestor->left;
           }
           else
            ancestor=ancestor->right;
         }
         return predeccessor;
     }
 }


int main(int argc, char**argv) {
	if(argc!=2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
    char str[200];
	BSTNode* root=savetofile(argv[1]);
	printf("Size of Tree: %d\n",size(root));
	printf("=====================================\n");
	printf("Height of Tree: %d\n", height(root));
	printf("=====================================\n");
	printf("Enter a sentence:\n");
	gets(str);
	char s[2]=" ";
	char* token;
	token = strtok(str,s);
	BSTNode* last;
	BSTNode* successor;
	BSTNode* predeccessor;
	char c[40];
	while(token!=NULL)
    {
        if(inordertraversal(root,token)==0)
        {
            printf("%s - ",token);
            last=getlastcontent(root,token);
            printf("%s,",last->word);
            successor=getsuccessor(root,last);
            printf("%s,",successor->word);
            predeccessor=getpredeccessor(root,last);
            printf("%s\n",predeccessor->word);
        }

        if(inordertraversal(root,token)==1)
            printf("%s - CORRECT\n",token);

        token=strtok(NULL,s);
    }
    printf("=====================================\n");
 }
