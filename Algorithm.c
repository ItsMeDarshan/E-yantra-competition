

/******************************************************************************   

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#define FALSE 0
#define TRUE 1
int or_path[12]={1,2,3,4,5,6,7,8,9,0,1,2};;
int dup_path[2];
int iter=0;
bool isPath=FALSE;
int mat_picked[]={0,0};
int Dist[12][12]={  {0, 5, 2, 5, 4, 7, 1, 4, 3, 6, 7,  3},//1
                    {5, 0, 5, 2, 7, 4, 4, 1, 6, 3, 7,  3},//2
                    {2, 5, 0, 5, 2, 7, 1, 4, 1, 6, 5,  5},//3
                    {5, 2, 5, 0, 7, 2, 4, 1, 6, 1, 5,  5},//4
                    {4, 7, 2, 7, 0, 6, 3, 6, 1, 6, 3,  7},//5
                    {7, 4, 7, 2, 6, 0, 6, 3, 6, 1, 3,  7},//6
                    {1, 4, 1, 4, 3, 6, 0, 3, 2, 7, 6,  4},//h1
                    {4, 1, 4, 1, 6, 3, 3, 0, 7, 2, 6,  4},//h2
                    {3, 6, 1, 6, 1, 6, 2, 7, 0, 5, 4,  6},//h3
                    {6, 3, 6, 1, 6, 1, 7, 2, 5, 0, 4,  6},//h4
                    {7, 7, 5, 5, 3, 3, 6, 6, 4, 4, 0, 10},//h5
                    {3, 3, 5, 5, 7, 7, 4, 4, 6, 6, 10, 0},//start
                 };
                 
int house[]={5,1,2,3,4};
int CM[] = {2,6,5,3,2,3,1,4,1,4};
struct available_mat
{
    int mat;
    struct available_mat *next;
};


int calculate_dist(int mat1,int mat2,int prev_H,int now_H)
{
    if(mat1==0 || mat2==0)
    {
        if(mat1!=0)
            return Dist[prev_H+5][mat1-1]+Dist[mat1-1][now_H+5];
        else(mat2!=0)
            return Dist[prev_H+5][mat2-1]+Dist[mat2-1][now_H+5];
        else
            return Dist[prev_H+5][now_H+5];
    }
    else
    {
        if(Dist[prev_H+5][mat1-1]<Dist[prev_H+5][mat2-1])
            return Dist[prev_H+5][mat1-1]+Dist[mat1-1][mat2-1]+Dist[mat2-1][now_H+5];
        else
            return Dist[prev_H+5][mat2-1]+Dist[mat2-1][mat1-1]+Dist[mat1-1][now_H+5];
    }
    
    
}

void decide_which_mat_take(struct available_mat* prev,struct available_mat* now,int bot_mat[],int H, int *b)
{
    int a=2;
    
    struct available_mat *p,*q,*s1,*s2,*temp;
     
    bool CM1=TRUE;
    bool CM2=TRUE;
    s1=now;
    s2=prev;
    int mat_for_house_H[] = {CM[2*H-1],CM[2*H-2]};
    //printf("mat_for_house_H %d = %d %d\n",H,mat_for_house_H[1],mat_for_house_H[0]);
    //printf("bot_mat %d %d\n",bot_mat[0],bot_mat[1]);
    //check bot_mat with mat req for given house
    if(bot_mat[0]==mat_for_house_H[0] && CM1)
    {
        
        CM1=FALSE;
        a--;
    }
    else if(bot_mat[0]==mat_for_house_H[1] && CM2)
    {
        
        CM2=FALSE;
        a--;
    }
    if(bot_mat[1]==mat_for_house_H[0] && CM1)
    {
        
        CM1=FALSE;
        a--;
    }
    else if(bot_mat[1]==mat_for_house_H[1] && CM2)
    {
        //printf("yhi h\n");
        CM2=FALSE;
        a--;
    }
    if(!CM1 && a==1)
    {
        q=malloc(sizeof(struct available_mat));
        now->mat=mat_for_house_H[1];
        //printf("cm1 %d\n",now->mat);
        now->next=q;
        now=q;
    }
    if(!CM2 && a==1)
    {
        q=malloc(sizeof(struct available_mat));
        now->mat=mat_for_house_H[0];
        //printf("%dcm2\n",now->mat);
        now->next=q;
        now=q;
    }
    bool ismat1=FALSE;
    bool ismat2=FALSE;
    bool for_H=FALSE;
    *b=a;
    int i=0;
    while(prev!=NULL)
    {
        //printf("prev%d\n",prev->mat);
        //if mat in bot is mat req for house
        if(a==0)
        
        {
        
            if((prev->mat!=mat_picked[0] || ismat1) && (prev->mat!=mat_picked[1] || ismat2) )
            {
                q=malloc(sizeof(struct available_mat));
                now->mat=prev->mat;
                
                //printf("now %d\n",now->mat);
                now->next=q;
                temp=now;
                now=q;
            }
            else
            {
                if(prev->mat==mat_picked[0])
                    ismat1=TRUE;
                else if(prev->mat==mat_picked[1])
                    ismat2=TRUE;
            }
            
            prev=prev->next;
        }
    
        else if(a==1)
       {
            if(!CM1)
            {
                
                if(((prev->mat!=mat_picked[0] || ismat1) && (prev->mat!=mat_picked[1] || ismat2) )&& (prev->mat!=mat_for_house_H[1] || for_H) )
                {
                    q=malloc(sizeof(struct available_mat));
                    now->mat=prev->mat;
                    //printf("h[1]%d\n",now->mat);
                    now->next=q;
                    temp=now;
                    now=q;
                }
                else
                {
                    if(prev->mat==mat_picked[0])
                        ismat1=TRUE;
                    else if(prev->mat==mat_picked[1])
                        ismat2=TRUE;
                    else if(prev->mat==mat_for_house_H[1])
                        for_H=TRUE;
                }
                
                prev=prev->next;
                
            }
            else if(!CM2)
            {
                
                if(((prev->mat!=mat_picked[0] || ismat1) && (prev->mat!=mat_picked[1] || ismat2) )&& (prev->mat!=mat_for_house_H[0] || for_H))
                {
                    q=malloc(sizeof(struct available_mat));
                    now->mat=prev->mat;
                    //printf("h[2]%d\n",now->mat);
                    now->next=q;
                    temp=now;
                    now=q;
                }
                else
                {
                    if(prev->mat==mat_picked[0])
                        ismat1=TRUE;
                    else if(prev->mat==mat_picked[1])
                        ismat2=TRUE;
                    else if(prev->mat==mat_for_house_H[0])
                        for_H=TRUE;
                }
                
                prev=prev->next;
            }
        }
        //mat req for house is not in bot hence take those material only
        else if(a==2)
        {
            //printf("oops prev null\n");
            prev=NULL;
            q=malloc(sizeof(struct available_mat));
            now->mat=mat_for_house_H[0];
            //printf("%d\n",now->mat);
            now->next=q;
            now=q;
            now->mat=mat_for_house_H[1];
            //printf("%d\n",now->mat);
        }
    }
    if(a!=2)
        now=temp;
    now->next=NULL;
    now=s1;
    prev=s2;
    //printf("now %d\n",now->mat);
}

// struct Node
// {
//     int house[5];
//     int start;
//     int size;   //how many house to consider will be decided by this
// }house_node;



void swap(int *x, int *y) 
{ 
    int temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 


int max_distance= 99999;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f(int step,int comb_of_HOUSE[5],struct available_mat* prev,int mat_in_bot[],int distance_upto_now)
{
    
    iter++;
    step++;
    if(step==4)
    {
        printf("akhirkar \n");
        printf("mat_in_bot %d %d\n",mat_in_bot[0],mat_in_bot[1]);
        //int distance = distance_upto_now+calculate_dist(mat_in_bot[0],mat_in_bot[1],comb_of_HOUSE[step-1],comb_of_HOUSE[step]);
        int distance=distance_upto_now+Dist[comb_of_HOUSE[step-1]+6][comb_of_HOUSE[step]+6];
        printf("sorry max_distance %d your distance %d\n",max_distance,distance);
        for(int i=0;i<9;i++)
            {
                printf("  nowpath %d",dup_path[i]); //i=%d i,
                
                
            }
        if(distance<max_distance)
        {
            for(int i=0;i<9;i++)
            {
                //printf("  path %d",dup_path[i]); //i=%d i,
                or_path[i]=dup_path[i];
                
            }
            //isPath=TRUE;
            max_distance=distance;
            or_path[3*(step-1)]=mat_in_bot[1];
            or_path[3*(step-1)+1]=mat_in_bot[0];
            or_path[3*(step-1)+2]=comb_of_HOUSE[step]+6;
            printf("max_distance achieved\n");
            for(int i=0;i<12;i++)
                printf("%d ",or_path[i]);
        }
    }
    else if(step!=4)
    {
        
        int new_mat_in_bot[2];
        new_mat_in_bot[0]=mat_in_bot[0];
        new_mat_in_bot[1]=mat_in_bot[1];
        int prev_m1=mat_picked[0];
        int prev_m2=mat_picked[1];
        //printf("step %d\n",step);
        struct available_mat *now,*availmat,*head,*comb1,*comb2,*q,*for_availmat,*for_prev;
        int a;
        now = malloc(sizeof(struct available_mat));
        availmat=malloc(sizeof(struct available_mat));
        
        
       //see available combination of available_materials
        decide_which_mat_take(prev, now, mat_in_bot, comb_of_HOUSE[step], &a);
        
    //this will be used for generating combination of materials
        comb1=now;
        comb2=now->next;
        
    //now combination of available materials
        
        head=availmat;
        for_prev=prev;
        bool ismat1=FALSE;
        bool ismat2=FALSE;
        bool CM1=FALSE;
        bool CM2=FALSE;
        //printf("availble mat list\n");
        while(prev!=NULL)
        {
            //making list for next available material
            if((prev->mat!=mat_picked[0] || ismat1) && (prev->mat!=mat_picked[1] || ismat2)  )
            {
                q=malloc(sizeof(struct available_mat));
                availmat->mat=prev->mat;
                for_availmat=availmat;
                //printf("%d ",availmat->mat);
                availmat->next=q;
                availmat=q;
            }
            else
            {
                if(prev->mat==mat_picked[0])
                    ismat1=TRUE;
                else if(prev->mat=mat_picked[1])
                    ismat2=TRUE;
            }
                
                prev=prev->next;
        }
        //printf("\nmat_in_bot %d %d\n",mat_in_bot[0],mat_in_bot[1]);
        //printf("a %d\n",a);
        availmat=for_availmat;
        availmat->next=NULL;
        availmat=head;
        prev=for_prev;
        
        
        //printf("max_distance %d your distance %d\n",max_distance,distance_upto_now);
        int distance;
        //begin the combination of available_materials
        if(a==0)
        {
            while(comb1->next!=NULL)
            {
                while(comb2!=NULL)
                {
                    // printf(" comb0 %d %d\n",comb1->mat,comb2->mat);
                    //put these 2 mat in bot as prev 2 will be placed in house
                    distance=distance_upto_now+calculate_dist(comb2->mat,comb1->mat,comb_of_HOUSE[step-1],comb_of_HOUSE[step]);
                    if(distance<max_distance)
                    {
                        // if (step==1)
                        //     printf("\n******%d  %d\n",comb1->mat,comb2->mat);
                        new_mat_in_bot[0]=comb2->mat;
                        new_mat_in_bot[1]=comb1->mat;
                        //isPath=FALSE;
                        dup_path[3*(step-1)]=comb1->mat;
                        dup_path[3*(step-1)+1]=comb2->mat;
                        dup_path[3*(step-1)+2]=comb_of_HOUSE[step]+6;
                        int M1=mat_picked[0];
                        int M2=mat_picked[1];
                        mat_picked[0]=comb1->mat;
                        mat_picked[1]=comb2->mat;
                        f(step, comb_of_HOUSE, availmat, new_mat_in_bot, distance);
                        mat_picked[0]=M1;
                        mat_picked[1]=M2;
                            
                        
                    }
                    
                    
                    
                    
                    
                    comb2=comb2->next;
                }
                
                comb1=comb1->next;
                comb2=comb1->next;
            }
        }
        else if(a==1)
        {
            
            while(comb2!=NULL)
            {
                
                distance=distance_upto_now+calculate_dist(comb2->mat,comb1->mat,comb_of_HOUSE[step-1],comb_of_HOUSE[step]);
                // if(step==1)
                //     printf("\n******%d  %d\n",comb1->mat,comb2->mat);
                if(distance<max_distance)
                {
                    for(int i=0;i<2;i++)
                    {
                        if(new_mat_in_bot[i]==CM[2*comb_of_HOUSE[step]-1] ||  new_mat_in_bot[i]==CM[2*comb_of_HOUSE[step]-2] )
                        {
                            
                            new_mat_in_bot[i]=comb2->mat;
                            break;
                        }
                    }
                    //isPath=FALSE;
                    //printf(" comb1 %d %d\n",comb1->mat,comb2->mat);
                    //printf("mat send %d %d\n",new_mat_in_bot[0],new_mat_in_bot[1]);
                    dup_path[3*(step-1)]=comb1->mat;
                    dup_path[3*(step-1)+1]=comb2->mat;
                    dup_path[3*(step-1)+2]=comb_of_HOUSE[step]+6;
                    int M1=mat_picked[0];
                    int M2=mat_picked[1];
                    mat_picked[0]=comb1->mat;
                    mat_picked[1]=comb2->mat;
                    f(step, comb_of_HOUSE, availmat, new_mat_in_bot, distance);
                    new_mat_in_bot[0]=mat_in_bot[0];
                    new_mat_in_bot[1]=mat_in_bot[1];
                    mat_picked[0]=M1;
                    mat_picked[1]=M2;
                    
                }
                comb2=comb2->next;
            }
        }
        else if(a==2)
        {
            distance=distance_upto_now+calculate_dist(comb2->mat,comb1->mat,comb_of_HOUSE[step-1],comb_of_HOUSE[step]);
            
            if(distance<max_distance)
            {
                //isPath=FALSE;
                dup_path[3*(step-1)]=comb1->mat;
                dup_path[3*(step-1)+1]=comb2->mat;
                
                dup_path[3*(step-1)+2]=comb_of_HOUSE[step]+6;
               // printf(" comb2 %d %d\n",comb1->mat,comb2->mat);
               // printf("cob2 mat_in_bot %d %d\n",mat_in_bot[0],mat_in_bot[1]);
                int M1=mat_picked[0];
                int M2=mat_picked[1];
                mat_picked[0]=comb1->mat;
                mat_picked[1]=comb2->mat;
                
                f(step, comb_of_HOUSE, availmat, new_mat_in_bot, distance);
                mat_picked[0]=M1;
                mat_picked[1]=M2;
                // if(isPath)
                // {
                //     path[3*(step-1)]=mat_in_bot[0];
                //     path[3*(step-1)+1]=mat_in_bot[1];
                //     path[3*(step-1)+2]=comb_of_HOUSE[step];
                // }
            }
        }
        
        
        mat_picked[0]=prev_m1;
        mat_picked[1]=prev_m2;
    }
    
}
void permute(int *a, int l, int r)   // (*f)(int ,int ,int ,int ,int) https://medium.com/@jraleman/c-programming-language-passing-a-function-as-a-parameter-90d52fe842ea
{ 
   int i; 
   if (l == r) 
   {
       
        printf("%d %d %d %d %d\n", a[0],a[1],a[2],a[3],a[4]); 
     
        
        int available_materials[] = {2,6,5,3,2,3,1,4,1,4};
        int bot_mat[] = {1,4};
        int distance=0;
        int step = 0;
        
        struct available_mat *head,*p,*prev,*q;
        // copying CM from array to linked list
        head=malloc(sizeof(struct available_mat));
        head->mat=CM[0];
        head->next=NULL;
        p=head;
        prev=head;
        for(int i=1;i<8;i++)
        {
            q=malloc(sizeof(struct available_mat));
            p->next=q;
            q->mat=CM[i];
            //printf("%d ",q->mat);
            if(i<8)
                p=q;
            else
                p->next=NULL;
        }
        
        mat_picked[0]=bot_mat[0];
        mat_picked[1]=bot_mat[1];
        f(step,house,prev,bot_mat,distance); 
         //(*f)(step,a,available_materials[],mat_in_bot[],dist);
   }
   else
   { 
       for (i = l; i <= r; i++) 
       { 
          swap((a+l), (a+i)); 
          permute(a, l+1, r); 
          swap((a+l), (a+i)); //backtrack 
       } 
   } 
} 
  
/* Driver program to test above functions */
int main() 
{ 
    int a;
    int h[]={5,1,2,3,4};
    int bot_mat[]={1,4};
    int step=0;
    int distance=0;
    struct available_mat *head,*p,*prev,*q;
    // copying CM from array to linked list
    head=malloc(sizeof(struct available_mat));
    head->mat=CM[0];
    head->next=NULL;
    p=head;
    prev=head;
    for(int i=1;i<8;i++)
    {
        q=malloc(sizeof(struct available_mat));
        p->next=q;
        q->mat=CM[i];
        //printf("%d ",q->mat);
        if(i<8)
            p=q;
        else
            p->next=NULL;
    }
    // while(prev!=NULL)
    // {
    //     printf("%d ",prev->mat);
    //     prev=prev->next;
    
    // }
    
    permute(house, 1, 4); 
    
    
    //f(step,h,prev,bot_mat,distance);
    for(int i=0;i<12;i++)
        printf("%d ",or_path[i]);
    printf("\niter %d",iter);
    return 0; 
} 
