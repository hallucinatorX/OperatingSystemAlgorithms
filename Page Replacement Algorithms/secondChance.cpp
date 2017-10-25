#include<bits/stdc++.h>

using namespace std;

int currentSize=0;
int inMemeory[100],refBit[100];
struct QNode
{
    int key,R;
    struct QNode *next;
};

struct Queue
{
    struct QNode *front, *rear;
};


struct QNode* newNode(int k,int r)
{
    struct QNode *temp = new (QNode);
    temp->key = k;
    temp->R = r;
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
void enQueue(struct Queue *q, int k,int r)
{

    struct QNode *temp = newNode(k,r);

    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

struct QNode *deQueue(struct Queue *q)
{

    if (q->front == NULL)
        return NULL;

    struct QNode *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    currentSize--;
    return temp;


}
void printCurrentFrame(struct Queue *q)
{
    struct QNode *temp = q->front;
    while(temp!=NULL)
    {
        cout<<"Process: "<<temp->key << " R:"<<temp->R<<", ";
        temp = temp->next;
    }
    cout<<endl;
}

bool processReplace(struct Queue *q, int k,int r)
{
    struct QNode *temp = q->front;
    while(temp!=NULL)
    {
        if(temp->R == 0){
            temp->key = k;
            cout<<"\tEnter R ";
            cin>>r;
            temp->R = r;
            frame = q;
            return true;
        }
        else{
            temp->R = 0;

            deQueue(q);
            enQueue(q,temp->key, temp->R);
        }

        temp = temp->next;
    }
    frame = q;
    return false;


}
bool processSearch(struct Queue *q, int k)
{
    struct QNode *temp = q->front;
    while(temp!=NULL)
    {
        if(temp->key==k){
            temp->R =1;
            return true;
        }

        temp = temp->next;
    }
    return false;


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
    int processKey, frameSize, pageFaults = 0,n;

    struct Queue *mem = createQueue();
    struct Queue *frame = createQueue();

    cout<<"Enter number of pages: ";
    cin>>n;
    cout<<"Enter frame size: ";
    cin>>frameSize;
    cout<<"Enter Key: "  ;
    for(int j = 0; j<n; j++)
    {

        cin>>processKey;
        inMemeory[j] = processKey;
    }


    for(int i=0; i<n; i++)
    {
        processKey= inMemeory[i];

        cout<<"For Page: "<<processKey<<endl;

        if(processSearch(frame,inMemeory[i]))
        {
            cout<<"\tAlready in page frame, use it."<<endl;
        }
        else
        {
            pageFaults++;
            cout<<"\tPage Fault occurred "<<endl;
            if(currentSize<frameSize)
            {
                enQueue(frame, inMemeory[i],0);
            }
            else
            {
                processReplace(frame, inMemeory[i],0);

            }

        }
        cout<< "\tIn Frame: ";
        printCurrentFrame(frame);
        //cout<<endl<<"Total Page Fault: "<<pageFaults<<endl;
    }



    return 0;
}
