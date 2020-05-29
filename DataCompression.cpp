#include<iostream>
#include<fstream>
#include<queue>
#include<map>
#include<string>
#include"BinaryTreeNode.h"
using namespace std;
string findcode(BinaryTreeNode<int>* root,int num)
{
 if(root==NULL)
 {
  return "";
 }
 if(((root->left==NULL)&&(root->right==NULL))&&(root->data==num))
 {
  return "found";
 }
 string  s="";
 string str=findcode(root->left,num);
 if(str=="found")
 {
  root->left=NULL;
  s="1"+s;
  return s;
 }
 if((str!="")&&(str!="found"))
 {
  s="1"+str;
  return s;
 }
 string st=findcode(root->right,num);
 if(st=="found")
 {
  root->right=NULL;
  s="0"+s;
  return s;
 }
 if((st!="")&&(st!="found"))
 {
  s="0"+st;
 }
 return s;
}
void encode(BinaryTreeNode<int>* root,int*arr)
{
  map<char,string> mp;
 for(int i=0;i<256;i++)
 {
  if(arr[i]>0)
  {
    string str=findcode(root,arr[i]);
    char ch=(char)i;
    mp[ch]=str;
    cout<<ch<<" code = "<<str<<endl;
  }
 }

}
void printTree(BinaryTreeNode<int>* root) {
	if (root == NULL) {
		return;
	}
	cout << root->data << ":";
	if (root->left != NULL) {
		cout << "L-" << root->left->data;
	}

	if (root->right != NULL) {
		cout << " R-" << root->right->data;
	}
	cout << endl;
	printTree(root->left);
	printTree(root->right);
}
BinaryTreeNode<int>* formTree(priority_queue<int,vector<int>,greater<int> > pq)
{
	if(pq.empty())
	{
		return NULL;
	}
  BinaryTreeNode<int>**ad=new BinaryTreeNode<int>*[10000];
  for(int i=0;i<10000;i++)
  {
    ad[i]=NULL;
  }
	BinaryTreeNode<int>*leaf1=new BinaryTreeNode<int>(pq.top());
	pq.pop();
    BinaryTreeNode<int>*leaf2=new BinaryTreeNode<int>(pq.top());
    pq.pop();
    BinaryTreeNode<int>*root=new BinaryTreeNode<int>(leaf1->data+leaf2->data);
    root->left=leaf1;
    root->right=leaf2;
    pq.push(root->data);
    ad[root->data]=root;
    while((!pq.empty())&&(pq.size()>1))
    {
    int min1=pq.top();
    pq.pop();
    int min2=pq.top();
    pq.pop();

    if(ad[min1]!=NULL||ad[min2]!=NULL)
    {
      if(((ad[min1]!=NULL)&&(ad[min2]!=NULL))&&(min1!=min2))
      {
        leaf1=ad[min1];
        ad[min1]=NULL;
        leaf2=ad[min2];
        ad[min2]=NULL;
      }
     else if(ad[min1]!=NULL)
      {
        leaf1=ad[min1];
        ad[min1]=NULL;
        leaf2=new BinaryTreeNode<int>(min2);
      }
      else
      {
        leaf1=ad[min2];
        ad[min2]=NULL;
        leaf2=new BinaryTreeNode<int>(min1);
      }
      BinaryTreeNode<int>*nroot=new BinaryTreeNode<int>(min1+min2);
      nroot->left=leaf1;
      nroot->right=leaf2;
      root=nroot;
      pq.push(nroot->data);
      ad[nroot->data]=nroot;
    }
    else
    {
      leaf1=new BinaryTreeNode<int>(min1);
      leaf2=new BinaryTreeNode<int>(min2);
      BinaryTreeNode<int>*troot=new BinaryTreeNode<int>(min1+min2);
      troot->left=leaf1;
      troot->right=leaf2;
      ad[troot->data]=troot;
      pq.push(troot->data);
    }
  }
    return root;
}
priority_queue<int,vector<int>,greater<int> > prqueues(int*ar)
{
priority_queue<int,vector<int>,greater<int> >p;
for(int i=0;i<256;i++)
{
	if(ar[i]>0)
	{
		p.push(ar[i]);
	}
}
return p;
}
int main()
{
	int ar[256];
	for(int i=0;i<256;i++)
	{
		ar[i]=0;
	}
	char ch;
	ifstream file("sample.txt");
	while(file.get(ch))
	{
     
     char c=ch;
     ar[c]++;
    }
    //---------------------------------------------------------------------------//
    /*FOR PRINTING THE FREQUENCY OF CHARACTERS.(TESTING FUNCTION)
     for(int i=0;i<256;i++)
    {
    	if(ar[i]>0)
    	{
    		cout<<"Count of "<<(char)i<<" is equal to="<<ar[i]<<endl;
    	}
    }*/
   //----------------------------------------------------------------------------//
   //Calling of prqueues in order to make min-heap
  priority_queue<int,vector<int>,greater<int> >pq= prqueues(ar);
  /*while(!pq.empty())
  {
  	cout<<pq.top()<<endl;
  	pq.pop();
  }*/
  //Making a binary tree with the help of priority queue
  BinaryTreeNode<int>*root=formTree(pq);
  printTree(root);
  cout<<endl;
  //Next step is to form codes from Binary tree.
  encode(root,ar);
    file.close();
    return 0;
}