/*
 * bheap.h
 *
 *  implement BiHeap and BiHeapNode data structure;
 *  support the following operation of Biheap: 
 *   Find_Min_Key, Merge, Union insert new node, Del_min, print
  */
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

#define NAN -1
#define LARGENUM 999999999999

class BiHeapNode;
class BiHeap{
 private:
  BiHeapNode * head;
  BiHeapNode * pre_min;
  BiHeapNode * ppmin;
 public:
  BiHeap();
  BiHeap(BiHeapNode * head_);
  ~BiHeap();
  BiHeapNode* Find_Min_Key();
  void BiHeap_Insert(int x);
  void BiHeap_Merge(BiHeap * H2);
  void BiHeap_Union(BiHeap * H3);
  BiHeap* BiHeap_Del_Min();
  BiHeap *BiHeapNode_Reverse();
  void BiHeap_Print();
};


BiHeap::~BiHeap(){
	delete this;
}
class BiHeapNode{
 private:
  BiHeapNode * parent;  // point to parent node
  BiHeapNode * sibling; // point to sibling node
  BiHeapNode * child; // point to child node (left child)
  int degree;  // the degree of this node
  int key; // the key vaule of this node

 public:
  friend BiHeapNode* BiHeapNode_Link(BiHeapNode * r,BiHeapNode * s);
  friend class BiHeap;
// constructors
  BiHeapNode();
  BiHeapNode(int key_);
  ~BiHeapNode();

};


BiHeapNode::~BiHeapNode(){
	delete this;
}
// print the binomial heap structure
void BiHeap::BiHeap_Print(){
	queue<BiHeapNode *> pt;
	queue<int> level;
	int start=1;
	BiHeapNode *pnode;
	pnode=head;
	if(pnode == NULL) return;
	int node_level=0;
	int cur_level;
	BiHeapNode *pchnode;
	cur_level=start;
	while(pnode){
		pt.push(pnode);
		level.push(cur_level);
		pnode=pnode->sibling;
	}

	while(!pt.empty()){
		cur_level=level.front();
		if(node_level < cur_level){
			if(node_level > 0)
				cout<<endl;
			node_level=cur_level;
			cout<<"Level ["<< node_level<<"]\t";
		}
		pnode=pt.front();
		pt.pop();
		cout<<pnode->key<<"\t";
		level.pop();
		if(pnode->child){
			pchnode=pnode->child;
			while(pchnode){
				pt.push(pchnode);
				level.push(cur_level+1);
				pchnode=pchnode->sibling;
			}
		}
	}
	cout<<endl;
	return;
}


BiHeapNode::BiHeapNode(int key_){
  parent=NULL;
  sibling=NULL;
  child=NULL;
  degree=0;
  key=key_;
}

BiHeapNode::BiHeapNode(){
  parent=NULL;
  sibling=NULL;
  child=NULL;
  degree=NAN;
  key=NAN;
}






BiHeap::BiHeap(){
  head=NULL;
  pre_min=NULL;
  ppmin=NULL;
}

BiHeap::BiHeap(BiHeapNode *head_){
  head=head_;
  pre_min=NULL;
  ppmin=NULL;
}

// find the min node in binomial tree
BiHeapNode* BiHeap::Find_Min_Key(){
  BiHeapNode * pos, * pmin,*pnext;
  int min;
  pre_min=NULL;
  ppmin=NULL;
  pos=head;
  pnext=pos->sibling;
  pmin=pos;
  min=pos->key;
  while (pnext ){
    if(pnext->key < min){
      min=pnext->key;
      pmin=pnext;
      pre_min=pos;
    }
    pos=pnext;
    pnext=pnext->sibling;
  }
  ppmin=pmin;
  return pmin;

}

void BiHeap::BiHeap_Insert(int x){
  BiHeapNode *p_xnode= new BiHeapNode(x);
  BiHeap * tmp = new BiHeap(p_xnode);
  BiHeap_Union(tmp);
  return;
}

// s becomes the subtree of r
BiHeapNode* BiHeapNode_Link( BiHeapNode * r, BiHeapNode * s){
	s->parent=r;
  s->sibling=r->child;
  r->child=s;
  r->degree+=1;
  return r;
}

// merge H2(another binomial heap) with this heap

void BiHeap::BiHeap_Merge(BiHeap*H2){
  BiHeapNode * h1_p,* h2_p, *h1_next_p, *h2_next_p;
  if (head == NULL && H2->head!=NULL){
	  head=H2->head;
	  return;
  }
  else if (H2->head==NULL){
	  return;
  }
  if(H2->head->degree>=head->degree){
	  h1_p=head;
	  h2_p=H2->head;
  }
  else{
	  h2_p=head;
	  h1_p=H2->head;
	  head=h1_p;
  }
  h1_next_p=h1_p->sibling;
  while ( h1_p!=NULL && h2_p !=NULL){
	  h2_next_p=h2_p->sibling;
	  if(h1_next_p==NULL){
	      h1_p->sibling=h2_p;
	      break;
	  }
	  if (h1_p->degree <= h2_p->degree && h2_p->degree<h1_next_p->degree){
    		h1_p->sibling=h2_p;
    		h1_p=h2_p;
    		if (h2_next_p==NULL){
    			h2_p->sibling=h1_next_p;
    			break;
    		}
    		else{

    			h2_p=h2_next_p;
    		}
	  }
	  else {
		  if(h2_p->degree==h1_next_p->degree)
		      {
			  	h1_p->sibling=h2_p;
		      	h2_p->sibling=h1_next_p;
		      	h2_p=h2_next_p;
		      }
		  	  h1_p=h1_next_p;
		  	  h1_next_p=h1_next_p->sibling;
		  	}

  }
	  return;
  }

void BiHeap::BiHeap_Union(BiHeap * H3){
	BiHeap_Merge(H3);
	if(head==NULL){
		return;
	}
	BiHeapNode * pre, * pos, * next;
	pre=NULL;
	pos=this->head;
  next=pos->sibling;
  while(next !=NULL){
    if (pos->degree != next->degree || (next->sibling!=NULL && next->sibling->degree==pos->degree)){
      pre=pos;
      pos=next;
    }
    else if(pos->key <=next->key){
      pos->sibling=next->sibling;
      pos=BiHeapNode_Link(pos, next);
    }
    else{
    	if (pre==NULL){
    		this->head=next;
    	}
    	else {
    		pre->sibling=next;
    	}
      pos=BiHeapNode_Link(next, pos);
    }
     next=pos->sibling;
  //   ti_union_loop+=clock()-loop;
  }
  return;
}
// used when delete min
BiHeap * BiHeap::BiHeapNode_Reverse(){
  BiHeapNode *npos, *nnext1, *nnext2;
  BiHeap * tmp=new BiHeap();
  if(ppmin->degree==NAN || ppmin->degree==0){
	  tmp->head=NULL;
	  return tmp;
  }
  npos=ppmin->child;
  npos->parent=NULL;
  nnext1=npos->sibling;
  npos->sibling=NULL;
  int i=0;
    while(nnext1 != NULL){
    	i=i+1;
      nnext2=nnext1->sibling;
      nnext1->sibling=npos;
      npos=nnext1;
      nnext1=nnext2;
    }

    tmp->head=npos;

    return tmp;
}

BiHeap*  BiHeap::BiHeap_Del_Min(){
	clock_t start;
	start=clock();
	Find_Min_Key();
	if (pre_min==NULL){
	  head=ppmin->sibling;
	}
	else if(pre_min != NULL){
	  pre_min->sibling=ppmin->sibling;
	}
	BiHeap* H2=BiHeapNode_Reverse();
	BiHeap_Union(H2);
  return this;
}
