#define _CRT_SECURE_NO_WARNINGS

#include		<stdio.h>
#include		<stdlib.h>

#define		INF		9999

//type definition
typedef struct node {
	int key;
	struct page* child;		//�ڽ� �������� ����Ų��.
}node;
typedef struct node* link;

typedef struct page {
	int pgid;						//������ id
	int degree;					//���� ���� (�ڽ� �������� ��)
	link cont[2];			//���� ��� �迭
	struct page* parent;		//�θ� ������
	struct page* child;			//�ڽ� ������
}page;
typedef struct page* plink;

//global
plink root = NULL;
int id = 1;
int ptemp_from;
FILE* rfp;

link createNode(int key) {
	link temp = (link)malloc(sizeof(node));
	temp->key = key;
	temp->child = NULL;
	return temp;
}

plink createPage() {
	plink temp = (plink)malloc(sizeof(page));
	temp->parent = NULL;
	temp->child = NULL;
	temp->pgid = id++;
	temp->cont[0] = NULL;
	temp->cont[1] = NULL;
	temp->degree = 0;
	return temp;
}

int getAddress(plink input, int key) {
	if (key <= input->cont[0]->key) return 0;		//left
	if (input->cont[1] == NULL) return 2;				//right

	if (input->cont[1]->key < key) return 2;			//right
	else return 1;														//middle
}
//�ش� Ű�� input ������ ������ ��� node�� child�� �������� �ּҸ� �˷���.

void insert_page(plink* p, link input) {
	if (input->key >= (*p)->cont[0]->key)
		(*p)->cont[1] = input;
	else {
		(*p)->cont[1] = (*p)->cont[0];
		(*p)->cont[0] = input;
	}
}
//�������� ������ ��ġ�� ��带 �����ϴ� �Լ�.



void split(plink* root, link input, plink ptemp) {
	int addr = getAddress(*root, input->key);
	link left = NULL, middle = NULL, right = NULL;

	if (addr == 0) {
		left = input;
		middle = (*root)->cont[0];
		right = (*root)->cont[1];
	}
	else if (addr == 1) {
		left = (*root)->cont[0];
		middle = input;
		right = (*root)->cont[1];
	}
	else if (addr == 2) {
		left = (*root)->cont[0];
		middle = (*root)->cont[1];
		right = input;
	}

	//root�� ��ȭ�Ǿ��� ���
	if ((*root)->parent == NULL) {
		plink pleft = createPage();
		plink pright = createPage();
		plink childtemp = (*root)->cont[1]->child;

		pleft->parent = *root;
		pleft->cont[0] = left;

		pright->parent = *root;
		pright->cont[0] = right;

		(*root)->cont[0] = middle;
		(*root)->cont[1] = NULL;
		(*root)->degree += 2;
		(*root)->cont[0]->child = pleft;

		link temp = (*root)->child;
		(*root)->child = pright;
		pright->child = temp;
		if (ptemp != NULL) {
			switch (addr) {
			case 0:
				pleft->cont[0]->child = ptemp;
				if (childtemp) {
					childtemp->parent = pright;
					pright->cont[0]->child = childtemp;
				}
				break;
			case 1:
				pleft->child = ptemp;
				if (childtemp) {
					childtemp->parent = pright;
					pright->cont[0]->child = childtemp;
				}
				break;
			case 2:
				pright->cont[0]->child = ptemp;
				if (childtemp) {
					childtemp->parent = pleft;
					pleft->child = childtemp;
				}
				break;
			}
		}
		return;
	}

	//����Ʈ���� ��ȭ�Ǿ��� ���
	plink brother = createPage();
	brother->cont[0] = left;
	(*root)->cont[0] = right;
	(*root)->cont[1] = NULL;
	//���� �������� ������ left���� �־��ش�.

	//ptemp �ȿ� �������� ����ִٸ�, �̸� �����ϰ� �ٿ��ش�.
	if (ptemp != NULL) {
		switch (addr) {
		case 0:
			brother->cont[0]->child = ptemp;
			break;
		case 1:
			brother->child = ptemp;
			break;
		case 2:
			(*root)->cont[0]->child = ptemp;
			break;
		}
	}

	//�θ� �������� ��ȭ ���¶��, ���� �������� ÷���� �� �Լ��� ��ͽ����Ѵ�.
	//input ���ڿ� middle�� �־� �θ� �������� pass�Ѵ�.
	if ((*root)->parent->degree == 3) {
		plink parent = (*root)->parent;
		ptemp_from = addr;
		split(&parent, middle, brother);
	}

	//�θ� ������ ������ ������ �ִٸ�, ���� �������� �θ� �������� �ڽ����� �ٴ´�.
	else {
		//root�� �θ� �������� cont[0]����� �ڽ��̶��, root�� cont[1]�� �ڽ����� �ű�� ���� �������� cont[0] �ڽ����� ���δ�.
		plink parent = (*root)->parent;
		insert_page(&parent, middle);
		if ((*root) == parent->cont[0]->child) {
			parent->cont[1]->child = (*root);
			parent->cont[0]->child = brother;
		}
		else {
			//�θ� �������� ���� �ڽ��̶��(�ֿ��), ���� �������� cont[1]�� �ڽ����� ���δ�.
			parent->cont[1]->child = brother;
		}
		//���ο� �������� �ٿ��ٸ�, middle��带 �θ� �������� �ִ´�.
		brother->parent = parent;
		parent->degree += 1;
		
	}

}

void insert(plink* root, int key) {
	if (*root == NULL) {
		link temp = createNode(key);
		plink ptemp = createPage();
		ptemp->cont[0] = temp;
		*root = ptemp;
		return;
	}	//root�� NULL�� ���

	plink head = *root;
	//key�� �� ��ġ(���)�� ã�´�.
	while (1) {
		//���� ���� �ִ� �������� �ڽ��� ������ Ȯ��.
		if (head->degree == 0) {
			//�ڽ��� ���ٸ�, ���� ���� �ִ� �������� ��带 �߰��Ѵ�.
			//�� �� �ڸ��� ���ٸ�, Ʈ���� split�Ѵ�.
			if (head->cont[1] != NULL) {
				split(&head, createNode(key), NULL);
			}
			else {
				//�ڸ��� �ִٸ�, key���� ���� �˸��� ��ġ�� �����Ѵ�.
				insert_page(&head, createNode(key));
			}
			return;
		}
		//�ڽ��� �ִٸ�, key���� ���� �˸��� �ڽ� �������� �̵��Ѵ�. (���� ��, �������� ���� �����.)
		int addr = getAddress(head, key);
		if (addr == 0 || addr == 1) {			//left
			if (head->cont[addr]->child == NULL) {
				plink ptemp = createPage();
				head->cont[addr]->child = ptemp;
				ptemp->parent = head->cont[addr];
				head->degree++;
			}
			head = head->cont[addr]->child;
			continue;
		}
		if (addr == 2) {			//right
			if (head->child == NULL) {
				plink ptemp = createPage();
				head->child = ptemp;
				ptemp->parent = head;
				head->degree++;
			}
			head = head->child;
			continue;
		}
	}
}

void print(plink root) {
	if (root == NULL) return;
	int pid, n, cid, cpage;
	if (root->parent == NULL) pid = -1; else pid = root->parent->pgid;
	if (root->cont[1] == NULL) n = 1; else n = 2;
	if (root->child == NULL) cid = -1;  else cid = root->child->pgid;
	printf("[PageID = %d][ParentID = %d][Nodes = %d][Last ChildPage ID = %d]", root->pgid, pid, n, cid);
	cpage = (root->cont[0]->child) ? root->cont[0]->child->pgid : -1;
	printf("\n(key=%d, child_pageID=%d)", root->cont[0]->key, cpage);
	if (root->cont[1] != NULL) {
		cpage = (root->cont[1]->child) ? root->cont[1]->child->pgid : -1;
		printf(" (key=%d, child_pageID=%d)", root->cont[1]->key, cpage);
	}
	printf("\n\n");
	print(root->cont[0]->child);
	if (root->cont[1] != NULL) print(root->cont[1]->child);
	print(root->child);
}


void main() {
	int inputsize, key;
	rfp = fopen("input.txt", "r");
	if (rfp == NULL) {
		perror("file open error");
		exit(1);
	}

	fscanf(rfp, "%d\n", &inputsize);
	for (int i = 0; i < inputsize; i++) {
		fscanf(rfp, "%d ", &key);
		insert(&root, key);
		printf("inserting %d. . .\n", key);
		print(root);
	}

	fclose(rfp);
}