#include<iostream>
using namespace std;


void buildTree(int *a,int *tree,int s,int e,int index){
	//Base Case
	if(s>e){
		return;
	}
	if(s==e){
		tree[index] = a[s];
		return;
	}
	//Rec Case
	int mid = (s+e)/2;
	buildTree(a,tree,s,mid,2*index);
	buildTree(a,tree,mid+1,e,2*index+1);
	tree[index] = min(tree[2*index],tree[2*index + 1]);
	return;
}

int query(int *tree,int index,int s,int e,int qs,int qe){
	//No Overlap
	if(qs>e || qe<s){
		return INT_MAX;
	}
	else if(s>=qs && e<=qe){
		return tree[index];
	}
	else{
		int mid = (s+e)/2;
		int left = query(tree,2*index,s,mid,qs,qe);
		int right = query(tree,2*index+1,mid+1,e,qs,qe);
		return min(left,right);
	}
}

//Update - Point Update Vs Range Update
void update(int *tree,int index,int i,int increment,int s,int e){
	//Out of bounds
	if(i>e || i<s){
		return;
	}
	//Leaf Node- Always Update (one leaf node of this type)
	if(s==e){
		tree[index] += increment;
		return;
	}
	else{
		//call both sides
		int mid  = (s+e)/2;
		update(tree,2*index,i,increment,s,mid);
		update(tree,2*index+1,i,increment,mid+1,e);
		tree[index]  = min(tree[2*index],tree[2*index+1]);
	}
	return;
}

//Homework
//void rangeUpdate(___________i,j,inc________);


int main(){
	int a[] = {1,3,2,7,5};
	int n = 5;
	int *tree = new int[4*n+1];
	buildTree(a,tree,0,n-1,1);

	/*for(int i=1;i<10;i++){
		cout<<tree[i]<<" ";
	}*/

	update(tree,1,0,10,0,n-1);
	update(tree,1,1,10,0,n-1);

	int q;
	cin>>q;

	while(q--){
		int qs,qe;
		cin>>qs>>qe;
		cout<<query(tree,1,0,n-1,qs,qe)<<endl;

	}


	return 0;
}