#include<bits/stdc++.h>

using namespace std;

int currentSize=0;
int inMemeory[100],refBit[100],modBit[100];

struct QNode
{
    int key,R,M,C;
    struct QNode *next;
};

struct Queue
{
    struct QNode *front, *rear;
};


struct QNode* newNode(int k,int r,int m)
{
    struct QNode *temp = new (QNode);
    temp->key = k;
    temp->R = r;
    temp->M = m;
    if(r==0 and m ==0)
        temp->C = 0;
    else if(r==0 and m ==1)
        temp->C = 1;
    else if(r==1 and m ==0)
        temp->C = 2;
    else
        temp->C =3;

    temp->next = NULL;

    currentSize++;
    return temp;
}

struct Queue *createQueue()
{
    struct Queue *q = new (Queue);
    q->front = q->rear = NULL;
    return q;
}

    struct Queue *mem = createQueue();
    struct Queue *frame = createQueue();


void enQueue(struct Queue *q, int k,int r,int m)
{

    struct QNode *temp = newNode(k,r,m);

    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}


void printCurrentFrame(struct Queue *q)
{
    struct QNode *temp = q->front;
    while(temp!=NULL)
    {
        cout << "Process: "<<temp->key << " R:"<<temp->R<<" M:"<<temp->M<< ", ";
        temp = temp->next;
    }
    cout<<endl;
}

bool processSearch(struct Queue *q, int k,int r, int m)
{
    struct QNode *temp = q->front;
    while(temp!=NULL)
    {
        if(temp->key==k && temp->R == r && temp->M==m)
        {
            temp->R == 1;
            return true;
        }

        temp = temp->next;
    }
    return false;


}
void processReplace(struct Queue *q, int k1,int k2, int r,int m)
{
    struct QNode *temp = q->front;
    while(temp!=NULL)
    {
        if(temp->key==k1)
        {
            temp->key = k2;
            cout<<"Enter R ";
            cin>>r;
            temp->R =r;
            cout<<"Enter M ";
            cin>>r;
            temp->M = m;
        }
        temp = temp->next;
    }
}
int getLeastValuedPage(struct Queue *q)
{
    int k1=0,i=0;


    struct QNode *temp,*temp1 = new (QNode);
    temp,temp1 = q->front;
    while(temp!=NULL)
    {
        while(temp1->C==i)
        {
            k1 = temp1->key;
            return k1;
            temp1 = temp1->next;
        }
        if(i<4)
            i++;
    }
    temp = temp->next;
}


bool isExists(int inMemeory[], int k)
{
    for(int i=0; i<sizeof(inMemeory)/sizeof(int); i++)
    {
        if(inMemeory[i]==k)
            return true;
    }
    return false;
}
int main()
{
    int processKey, frameSize, pageFaults = 0,M,R,n;

    cout<<"Enter number of pages: ";
    cin>>n;
    cout<<"Enter frame size: ";
    cin>>frameSize;
    cout<<"Enter Key: "  ;
    for(int j = 0; j<n; j++)
    {

        cin>>processKey;
        inMemeory[j] = processKey;
        // enQueue(frame, processKey,R,M);
    }

    for(int i=0; i<n; i++)
    {
        cout<<"For Page: "<<inMemeory[i]<<endl;

        if(processSearch(frame,inMemeory[i],0,0))
        {
            cout<<"\tAlready in page frame, use it."<<endl;
        }
        else
        {
            pageFaults++;
            cout<<"\tPage Fault occurred "<<endl;
            if(currentSize<frameSize)
            {
                enQueue(frame, inMemeory[i],0,0);
            }
            else
            {

                processReplace(frame,getLeastValuedPage(frame),inMemeory[i],0,0);

            }

        }

        cout<< "\tIn Frame: ";
        printCurrentFrame(frame);


    }
    //cout<<endl<<"Total Page Fault: "<<pageFaults<<endl;

    return 0;
}
