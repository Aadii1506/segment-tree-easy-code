#include<iostream>
using namespace std;
//for building tree
void buildtree(int *arr,int *tree,int start,int end,int treenode){
    if(start==end){     //base case ki jb start or end dono equal h mtlb index arr ka return kr skte h
        tree[treenode]=arr[start];
        return;
    }
    int mid=(start+end)/2;      //mid nikalo or iske through 2 recursive call krdo ek left m or ek right
    buildtree(arr,tree,start,mid,2*treenode);
    buildtree(arr,tree,mid+1,end,2*treenode+1);
    tree[treenode]=tree[2*treenode]+tree[2*treenode+1]; //end m dono ka sum us final treenode mtlb parent m daldo and done
}
//for updating any value in tree
void updatetree(int* arr,int *tree,int start,int end,int treenode,int idx,int val){
    if(start==end){
        arr[start]=val;
        tree[treenode]=val; //final index jaha changes krna thaa krdo both in array and tree m
        return;
    }
    int mid=(start+end)/2;
    if(mid>idx){    //binary search ki trh chlo indexing to sorted hi hoti na to krsktae
        updatetree(arr,tree,start,mid,2*treenode,idx,val);
    }
    else{
        updatetree(arr,tree,mid+1,end,2*treenode+1,idx,val);
    }
    tree[treenode]=tree[2*treenode]+tree[2*treenode+1]; //last m tree ki logn  values update krdo and done
}
//koi range ka sum ka jrurt ho tb query raise kro left right m pass krke
int query(int *tree,int start,int end,int treenode,int left,int right){
    if(start>right||end<left)   //jo value chahiye vo completely out of range h to return 0
        return 0;
    if(start>=left&&end<=right) //jo value chahiye vo fully range m h to return that node itself
        return tree[treenode];
    //else part ki partially in range and partially out of range to recursion call krdia left right m
    int mid=(start+end)/2;
    int ans1=query(tree,start,mid,2*treenode,left,right);   //left se mid tk range m jo h uska sum
    int ans2=query(tree,mid+1,end,2*treenode+1,left,right); //mid+1 se right tk range m jo h uska sum
    return ans1+ans2;   // return their sum whatever
}

int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int tree[4*n];  //4*n size ka hi bnega tree or indexing hm 1 se store krre h gp ke through nikalenge like 2^0+2^1+2^2+-------2^(ceil logn) to iska sum approx 4*n aayega and the reason space ka gdbd na ho to 4n size lenge
    buildtree(arr,tree,0,n-1,1);
    for(int i=1;i<4*n;i++){
        cout<<tree[i]<<" ";
    }
    cout<<endl;
    updatetree(arr,tree,0,n-1,1,4,7);
    for(int i=1;i<2*n;i++){
        cout<<tree[i]<<" ";
    }
    cout<<endl;
    // last m jo 2,5 pass h vo range h ki is range ka sum chahiye.
    int ans=query(tree,0,n-1,1,2,5);
    cout<<ans<<endl;

}