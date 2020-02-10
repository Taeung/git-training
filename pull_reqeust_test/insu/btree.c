#define _CRT_SECURE_NO_WARNINGS

#include		<stdio.h>
#include		<stdlib.h>

#define		INF		9999

//type definition
typedef struct node {
	int key;
	struct page* child;		//자식 페이지를 가리킨다.
}node;
typedef struct node* link;

typedef struct page {
	int pgid;						//페이지 id
	int degree;					//현재 차수 (자식 페이지의 수)
	link cont[2];			//내용 노드 배열
	struct page* parent;		//부모 페이지
	struct page* child;			//자식 페이지
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
//해당 키가 input 페이지 내에서 어느 node의 child로 내려갈지 주소를 알려줌.

void insert_page(plink* p, link input) {
	if (input->key >= (*p)->cont[0]->key)
		(*p)->cont[1] = input;
	else {
		(*p)->cont[1] = (*p)->cont[0];
		(*p)->cont[0] = input;
	}
}
//페이지의 적절한 위치에 노드를 삽입하는 함수.



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

	//root이 포화되었을 경우
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

	//서브트리가 포화되었을 경우
	plink brother = createPage();
	brother->cont[0] = left;
	(*root)->cont[0] = right;
	(*root)->cont[1] = NULL;
	//형제 페이지를 생성해 left값을 넣어준다.

	//ptemp 안에 페이지가 들어있다면, 이를 적절하게 붙여준다.
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

	//부모 페이지가 포화 상태라면, 형제 페이지를 첨부해 이 함수를 재귀실행한다.
	//input 인자에 middle을 넣어 부모 페이지에 pass한다.
	if ((*root)->parent->degree == 3) {
		plink parent = (*root)->parent;
		ptemp_from = addr;
		split(&parent, middle, brother);
	}

	//부모 페이지 차수에 여유가 있다면, 형제 페이지는 부모 페이지의 자식으로 붙는다.
	else {
		//root이 부모 페이지의 cont[0]노드의 자식이라면, root을 cont[1]의 자식으로 옮기고 형제 페이지를 cont[0] 자식으로 붙인다.
		plink parent = (*root)->parent;
		insert_page(&parent, middle);
		if ((*root) == parent->cont[0]->child) {
			parent->cont[1]->child = (*root);
			parent->cont[0]->child = brother;
		}
		else {
			//부모 페이지의 직속 자식이라면(최우단), 형제 페이지를 cont[1]의 자식으로 붙인다.
			parent->cont[1]->child = brother;
		}
		//새로운 페이지를 붙였다면, middle노드를 부모 페이지에 넣는다.
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
	}	//root이 NULL인 경우

	plink head = *root;
	//key가 들어갈 위치(노드)를 찾는다.
	while (1) {
		//현재 보고 있는 페이지의 자식이 없는지 확인.
		if (head->degree == 0) {
			//자식이 없다면, 현재 보고 있는 페이지에 노드를 추가한다.
			//이 때 자리가 없다면, 트리를 split한다.
			if (head->cont[1] != NULL) {
				split(&head, createNode(key), NULL);
			}
			else {
				//자리가 있다면, key값에 따라 알맞은 위치에 삽입한다.
				insert_page(&head, createNode(key));
			}
			return;
		}
		//자식이 있다면, key값에 따라 알맞은 자식 페이지로 이동한다. (없을 시, 페이지를 새로 만든다.)
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