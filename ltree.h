#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define NA 99999999

// LtreeNode: Inner nodes in leftist tree
class LtreeNode{
private:
	int key; // key value
	int s; // height function
	LtreeNode *lchild, *rchild; // pointer to left child and right child
public:
	friend class Ltree;
	friend void LtreeNode_Merge(LtreeNode * &x_,LtreeNode *y_);
	friend void LtreeNode_Swap(LtreeNode *&x_, LtreeNode *&y_);
//	constructor
	LtreeNode();
	LtreeNode(int key_):key(key_){
		s=1;
		lchild=NULL;
		rchild=NULL;
	}
};

LtreeNode::LtreeNode(){
	lchild=NULL;
	rchild=NULL;
	key=NA;
	s=1;
}


class Ltree{
public:
	LtreeNode *head;   // point to the head node of tree
public:
// constructors:
	Ltree(){
		head=NULL;
	}
	Ltree(LtreeNode *pnode_){
		head=pnode_;
	}
	Ltree(Ltree *ptree_){
		head=ptree_->head;
	}
// *****end of constructors*****
	void Ltree_Del_Min(); // delete min
	void Ltree_Insert(int key_); // insert a node with key value
	void Ltree_Merge(Ltree *ptree_);
	void Ltree_Print();
};

// print the tree's structure
// use queque as the tool
void Ltree::Ltree_Print(){
	if (head ==NULL){
		return;
	}
	queue<LtreeNode *> pt;
	queue<int> level;
	int p_start=1;
	pt.push(head);
	level.push(p_start);
	int p_level=0;
	while(!pt.empty()){
		int top_level=level.front();
		level.pop();
		if(p_level < top_level){
		if(p_level > 0)
			cout<<endl;
		p_level=top_level;
		cout<<"Level "<<p_level<<":";
		}
		LtreeNode *p=pt.front();
		cout<<p->key<<" ";
		pt.pop();
		if(p->lchild){
			pt.push(p->lchild);
			level.push(top_level+1);
		}
		if(p->rchild){
			pt.push(p->rchild);
			level.push(top_level+1);
		}
	}
	cout<<endl;
	return;
}

// delete min
void Ltree::Ltree_Del_Min(){
	LtreeNode *x, *y;
	x=head->lchild;
	y=head->rchild;
// merge the left child subtree with the right child subtree
	LtreeNode_Merge(x,y);
	head=x;
	return;
}

void Ltree::Ltree_Insert(int key_){
	LtreeNode *pnode=new LtreeNode(key_);
	LtreeNode_Merge(this->head,pnode);
	return;
}

// swap the left child with the right child when s of left is larger than right
void LtreeNode_Swap(LtreeNode *&x_, LtreeNode *&y_){
	LtreeNode * tmp;
	tmp=x_;
	x_=y_;
	y_=tmp;
	return;
}


void LtreeNode_Merge(LtreeNode *&x_, LtreeNode *y_){
	if(y_==NULL) return;
	if(x_==NULL){
		x_=y_;
		return;
	}
	if(x_->key > y_->key){
		LtreeNode_Swap(x_,y_);
	}
	LtreeNode_Merge(x_->rchild,y_);
	if(x_->lchild ==NULL){
		x_->lchild=x_->rchild;
		x_->rchild=NULL;
		x_->s=1;
	}
	else if (x_->rchild==NULL){
		x_->s=1;
	}
	else{
		if(x_->lchild->s < x_->rchild->s)
			LtreeNode_Swap(x_->lchild, x_->rchild);
		x_->s=x_->rchild->s+1;

		}
	return;
}
