#include <iostream>

using namespace std;

struct Node{
    Node* prev;
    Node *children[4];
    int state[3][3];
    bool goal;
    Node(){//designed for root node.
        prev=nullptr;
        for(int i =0;i<4;i++){
            children[i]=nullptr;
        }
    }
    Node(Node*p){
        prev=p;
        for(int i =0;i<4;i++){
            children[i]=nullptr;
        }
    }
    void SetPrev(Node* p){
        prev=p;
    }
    void SetState(int m[3][3]){
        for(int i =0;i<3;i++){
            for(int j=0;j<3;j++){
                state[i][j]=m[i][j];
            }
        }
    }
    void SetChildren(int m[3][3]){
        
        for(int i =0;i<3;i++){
            for(int j=0;j<3;j++){
                if(m[i][j]==0){
                    if(i!=0){//if blank is not in top row
                        int temp = m[i-1][j];
                        m[i-1][j]=0;
                        m[i][j]=temp;
                        if(m!=prev->state){//This weeds out endless loops
                            children[1]=new Node(this);//set down
                            children[1]->SetState(m);
                            if(!(children[1]->isGoal())){//Stops upon reaching a goal state
                                children[1]->SetChildren(m);
                            }
                        }
                    }
                    m=state;
                    if(i!=2){//if blank is not in bottom row
                        int temp = m[i+1][j];
                        m[i+1][j]=0;
                        m[i][j]=temp;
                        if(m!=prev->state){
                            children[2]=new Node(this);//set up
                            children[2]->SetState(m);
                            if(!(children[2]->isGoal())){//Stops upon reaching a goal state
                                children[2]->SetChildren(m);
                            }
                        }
                    }
                    m=state;
                    if(j!=0){//if blank is not in left column
                        int temp = m[i][j-1];
                        m[i][j-1]=0;
                        m[i][j]=temp;
                        if(m!=prev->state){
                            children[0]=new Node(this);//set left
                            children[0]->SetState(m);
                            if(!(children[0]->isGoal())){//Stops upon reaching a goal state
                                children[0]->SetChildren(m);
                            }
                        }
                    }
                    m=state;
                    if(j!=2){//if blank is not in right column
                        int temp = m[i][j+1];
                        m[i][j+1]=0;
                        m[i][j]=temp;
                        if(m!=prev->state){
                             children[3]=new Node(this);//set right
                            children[3]->SetState(m);
                            if(!(children[3]->isGoal())){//Stops upon reaching a goal state
                                children[3]->SetChildren(m);
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    bool isGoal(){
        int correctValues=0;
        int currVal=1;
        for(int i=0;i<3;i++){
            for(int j=0;j<2;j++){
                if(currVal==state[i][j]){
                    correctValues++;
                }
            }
        }
        if(correctValues>=8){
            goal=true;
            return true;
        }
        return false;
    }

};

int main(){

    int mat [3][3];
    cout<<"Enter the first row: ";
    int num;
    for(int i=0;i<3;i++){
        cin>>num;
        mat[0][i]=num;
    }
    cout<<"Enter the second row: ";
    for(int i=0;i<3;i++){
        cin>>num;
        mat[1][i]=num;
    }
    cout<<"Enter the third row: ";
    for(int i=0;i<3;i++){
        cin>>num;
        mat[2][i]=num;
    }
    Node * root=new Node();
    root->SetState(mat);
    root->SetChildren(mat);
    //Matrix is now populated.
    
}