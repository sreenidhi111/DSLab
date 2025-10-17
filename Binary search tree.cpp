#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int key;
    struct Node *left, *right;
};
struct Node* newNode(int item) 
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node)); 
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
void inorder(struct Node* root) 
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) 
	return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) 
	return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else 
	{
        if (root->left == NULL && root->right == NULL) 
		{
            free(root);
            return NULL;
        } 
		else if (root->left == NULL) 
		{
            struct Node* temp = root->right;
            free(root);
            return temp;
        } 
		else if (root->right == NULL) 
		{
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
int main() 
{
    struct Node* root = NULL;
    int choice, val;
    while (1) 
	{
        printf("\n***** Binary Search Tree Menu *****\n");
        printf("1. Insert\n2. Search\n3. Delete\n4. Inorder Traversal\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
		{
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &val);
                if (search(root, val))
                    printf("Value %d found in the BST.\n", val);
                else
                    printf("Value %d not found.\n", val);
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                break;
            case 4:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

