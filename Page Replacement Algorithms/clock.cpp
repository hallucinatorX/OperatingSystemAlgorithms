#include<bits/stdc++.h>
using namespace std;
int currentSize=0;
int inMemeory[100],refBit[100],frameSize;
struct Node
{
    int data,R;
    struct Node *next;
};

struct Node *addToEmpty(struct Node *last, int data,int r)
{
    // This function is only for empty list
    if (last != NULL)
      return last;

    // Creating a node dynamically.
    struct Node *temp = new (Node);

    // Assigning the data.
    temp -> data = data;
    temp->R = r;
    last = temp;

    // Creating the link.
    last -> next = last;
    currentSize++;
    return last;
}



struct Node *addAfter(struct Node *last, int data,int r, int item,int r1)
{
    if (last == NULL)
        return NULL;

    struct Node *temp, *p;
    p = last -> next;
    do
    {
        if (p ->data == item)
        {
            temp = new (Node);
            temp -> data = data;
            temp->R = r;
            temp -> next = p -> next;
            p -> next = temp;

            if (p == last)
                last = temp;
            currentSize++;
            return last;
        }
        p = p -> next;
    }  while(p != last -> next);

    cout << item << " not present in the list." << endl;

   // currentSize++;
    return last->next;

}

void traverse(struct Node *last)
{
    struct Node *p;

    if (last == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }

    p = last -> next;

    do
    {
        cout << "Process: "<<p -> data << " R:"<<p->R<< ", ";
        p = p -> next;

    }
    while(p != last->next);

}
bool processSearch(struct Node *last, int k,int r)
{
     struct Node *p = new (Node);
     int count =0;
    if (last == NULL)
    {
        cout << "List is empty." << endl;
        return false;
    }

    p = last;

    do
    {

    count++;
        if(p->data ==k && p->R == r){
            p->R = 1;
            return true;
        }


         p = last -> next;
         if(count>frameSize)
            return false;
    }
    while(p != last);

    return false;
}
struct Node* processReplace(struct Node *last,int k,int r){
 struct Node *p,*temp = new (Node);

    if (last == NULL)
    {
        cout << "List is empty." << endl;
        return last;
    }



    do
    {
        p = last -> next;
        if(p->R == 0)
        {
            p->data = k;
            cout<<"\tEnter R ";
            cin>>r;
            p->R = r;


            if (p == last)
                last = temp;
            return last;
        }
        else
            p->R = 0;

    }
    while(1);

    return last;
}

int main()
{
    struct Node *last = NULL;
    int processKey, pageFaults = 0,n;

    cout<<"Enter number of pages: ";
    cin>>n;
    cout<<"Enter frame size: ";
    cin>>frameSize;

    for(int j = 0; j<n; j++)
    {
        cout<<"Enter Key: "  ;
        cin>>processKey;
        inMemeory[j] = processKey;
        cout<<"\tEnter Reference Bit: "  ;
        cin>>refBit[j];
        // enQueue(frame, processKey,R,M);
    }

    for(int i=0; i<n; i++)
    {
        processKey= inMemeory[i];

        cout<<"For Page: "<<processKey<<endl;
        //cout<<currentSize;

        if(processSearch(last,inMemeory[i], refBit[i]))
        {
            cout<<"\tAlready in page frame, use it."<<endl;
        }
        else
        {
            pageFaults++;
            cout<<"\tPage Fault occurred "<<endl;
            if(currentSize<frameSize)
            {
                if(i==0){
                    last = addToEmpty(last, inMemeory[i],refBit[i]);
                }
                else
                    last = addAfter(last, inMemeory[i],0, inMemeory[i-1],0);
            }
            else
            {
                processReplace(last, inMemeory[i],0);

            }

        }
        cout<< "\tIn Frame: ";
        traverse(last);
        cout<<endl;
       // printCurrentFrame(frame);


    }
    //cout<<"Total Page Fault: "<<pageFaults<<endl;



    return 0;
}
