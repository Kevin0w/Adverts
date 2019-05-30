#include "Local_Storage.h"

int main()
{
    sList_t *headReq = NULL;
    sList_t *headSell = NULL;
    FILE *fp = NULL;
    FILE *fp2 = NULL;
    int choice = 0;

    if((fp=fopen("requests.dat","rb"))==NULL){
        perror(NULL);
        exit(1);
    }
    if((fp2=fopen("sell.dat","rb"))==NULL){
        perror(NULL);
        exit(2);
    }
    headReq = readFromRequestFile(fp, headReq);
    headSell = readFromSellFile(fp2, headSell);

    do{
        printf("Menu:");
        printf("\n1. Check for matchings;");
        printf("\n2. Delete advert by id;");
        printf("\n3. Print all adverts;");
        printf("\n5. Exit.");

        do{
            printf("\n\nEnter your choice: ");
            scanf("%d",&choice);
            while(getchar()!='\n');
        }while(choice<1 || choice>5);

        if(choice == 1){

            if(headReq != NULL && headSell != NULL){
                //printf("THIS headReq->next: %p", headReq->next);
                checkForMatchings(headReq, headSell);
            }
            else{
                printf("\nNo adverts found.");
            }
        }
        if(choice == 2){

            if(headReq != NULL && headSell != NULL){
                deleteAdvert(headReq, headSell);
            }
            else{
                printf("\nNo entered adverts");
            }
        }
        if(choice == 3){
            printAllElements(headReq, headSell);
        }

        printf("\n");
    }while(choice != 5);



    fclose(fp);
    fclose(fp2);
    freeList(headReq, headSell);

    return 0;
}
//working
sList_t *readFromRequestFile(FILE *fp, sList_t *headReq)
{
     sList_t *nodeReq = NULL;
     sList_t *temp = NULL;

     while(!feof(fp)){

        //printf("\nheadReq = %p\n", headReq);
        //printf("\nnodeReq = %p", nodeReq);


        if(headReq == NULL){

            headReq = (sList_t *)malloc(sizeof(sList_t));
            fread(&headReq->payload, sizeof(sAdvert_t), 1, fp);
            nodeReq = headReq;

        }

        else{

            temp = (sList_t *)malloc(sizeof(sList_t));

            fread(&temp->payload, sizeof(sAdvert_t), 1, fp);

            nodeReq->next = temp;
            nodeReq = temp;
            temp = temp->next;

//            nodeReq->next = temp;
//
//            fread(&temp->payload, sizeof(sAdvert_t), 1, fp);
//            printf("\nheadReq = %p\n", headReq);
//            printf("\nheadReq -> next: %p\n", headReq->next);
//            printf("\nnode before temp = %p\n", nodeReq);
//            printf("temp: %p\n", temp);
//            printf("\nnodeReq->next: %p\n", nodeReq->next);
//            nodeReq = temp;
//            printf("\nnode after temp = %p\n", nodeReq);
//
//            nodeReq->next = NULL;
        }
//        printf("\nheadReq = %p\n", headReq);
//        printf("nodeReq: %p\n", nodeReq);
//        printf("Type:\t%s", nodeReq->payload.type);
//        printf("ID:\t%s", nodeReq->payload.id);
//        printf("Title:\t%s", nodeReq->payload.title);
//        printf("Price:\t%lf", nodeReq->payload.price);
//        printf("\n\n");
     }


     return headReq;
}
//working
sList_t *readFromSellFile(FILE *fp2, sList_t *headSell)
{
     sList_t *temp = NULL;
     sList_t *nodeSell = NULL;

     while(!feof(fp2)){


//        printf("\nheadSell = %p", headSell);
//        printf("\nnodeSell = %p", nodeSell);

        if(headSell == NULL){

            headSell = (sList_t *)malloc(sizeof(sList_t));

            fread(&headSell->payload, sizeof(sAdvert_t), 1, fp2);

            nodeSell = headSell;
        }
        else{
            temp = (sList_t *)malloc(sizeof(sList_t));

            fread(&temp->payload, sizeof(sAdvert_t), 1, fp2);

            nodeSell->next = temp;
            nodeSell = temp;
            temp = temp->next;
        }
     }

     return headSell;
}
//working
void checkForMatchings(sList_t *headReq, sList_t *headSell)
{
    sList_t *nodeReq = NULL;
    sList_t *nodeSell = NULL;
    int flag = 0;

    for(nodeReq = headReq; nodeReq != NULL; nodeReq = nodeReq->next){
        for(nodeSell = headSell; nodeSell != NULL; nodeSell = nodeSell->next){
            if(strcmp(nodeReq->payload.type, nodeSell->payload.type)==0){
                if(nodeReq->payload.price>=(nodeSell->payload.price - (nodeReq->payload.price/100)) && nodeReq->payload.price<=(nodeSell->payload.price + (nodeReq->payload.price/100))){

                    flag = 1;
                    printf("\n****Requested advert: ****\n");

                    printf("Type:\t%s", nodeReq->payload.type);
                    printf("ID:\t%s", nodeReq->payload.id);
                    printf("Title:\t%s", nodeReq->payload.title);
                    printf("Price:\t%lf", nodeReq->payload.price);


                    printf("\n\n****Selling advert: ****\n");

                    printf("Type:\t%s", nodeSell->payload.type);
                    printf("ID:\t%s", nodeSell->payload.id);
                    printf("Title:\t%s", nodeSell->payload.title);
                    printf("\nPrice:\t%lf\n", nodeSell->payload.price);

                }
            }
        }
    }

    if(flag == 0){
        printf("\nNo match\n");
    }
}

void deleteAdvert(sList_t *headReq, sList_t *headSell)
{
    sList_t *nodeReq = NULL;
    sList_t *prevReq = headReq;
    sList_t *nodeSell = NULL;
    sList_t *prevSell = headSell;
    char id_to_delete[MAX_SIZE];
    int flagReq = 0;

    //strcpy(id_to_delete, prevReq->payload.id);


    printf("\nEnter the ID of the advert you want to delete: ");
    fflush(stdin);
    fgets(id_to_delete, MAX_SIZE, stdin);

    for(nodeReq = prevReq->next; nodeReq != NULL; nodeReq = nodeReq->next, prevReq = prevReq->next){

        //deleting first element
        if(strcmp(headReq->payload.id, id_to_delete)==0){

            flagReq = 1;
            printf("\n*******DELETING*******\n");
            printf("\n****Requested advert: ****\n");

            printf("Type:\t%s", headReq->payload.type);
            printf("ID:\t%s", headReq->payload.id);
            printf("Title:\t%s", headReq->payload.title);
            printf("Price:\t%lf\n", headReq->payload.price);

            free(headReq);
            headReq = nodeReq;
            prevReq = headReq;
            nodeReq = headReq->next;
        }

        if(strcmp(nodeReq->payload.id,id_to_delete)==0){

            flagReq = 1;
            printf("\n*******DELETING*******\n");
            printf("\n****Requested advert: ****\n");

            printf("Type:\t%s", nodeReq->payload.type);
            printf("ID:\t%s", nodeReq->payload.id);
            printf("Title:\t%s", nodeReq->payload.title);
            printf("Price:\t%lf\n", nodeReq->payload.price);

            prevReq->next = nodeReq->next;
            free(nodeReq);
            nodeReq = prevReq->next;
        }
    }

    write_req_el(headReq);

    if(flagReq == 0){
        for(nodeSell = prevSell->next; nodeSell != NULL; nodeSell = nodeSell->next, prevSell = prevSell->next){

            //deleting first element
            if(strcmp(headSell->payload.id, id_to_delete)==0){

                flagReq = 1;
                printf("\n*******DELETING*******\n");
                printf("\n****Requested advert: ****\n");

                printf("Type:\t%s", headSell->payload.type);
                printf("ID:\t%s", headSell->payload.id);
                printf("Title:\t%s", headSell->payload.title);
                printf("Price:\t%lf\n", headSell->payload.price);

                free(headSell);
                headSell = nodeSell;
                prevSell = headSell;
                nodeSell = headSell->next;
            }

            if(strcmp(nodeSell->payload.id,id_to_delete)==0){

                flagReq = 1;
                printf("\n*******DELETING*******\n");
                printf("\n****Sell advert: ****\n");

                printf("Type:\t%s", nodeSell->payload.type);
                printf("ID:\t%s", nodeSell->payload.id);
                printf("Title:\t%s", nodeSell->payload.title);
                printf("Price:\t%lf\n", nodeSell->payload.price);

                prevSell->next = nodeSell->next;
                free(nodeSell);
                nodeSell = prevSell->next;
            }
        }
    }

    write_sell_el(headSell);

    if(flagReq == 0){
        printf("\nNot found\n");
    }

}
void write_req_el(sList_t *headReq)
{
    FILE *fp = NULL;
    sList_t *nodeReq = NULL;

    if((fp = fopen("Requests_after_editing","wb"))==NULL){
        perror(NULL);
        exit(654);
    }

    for(nodeReq = headReq; nodeReq != NULL; nodeReq = nodeReq->next){
        if(fwrite(&nodeReq,sizeof(sAdvert_t),1,fp)!=1){
            perror(NULL);
            fclose(fp);
            exit(-1);
        }
    }
}

void write_sell_el(sList_t *headSell)
{
    FILE *fp = NULL;
    sList_t *nodeSell = NULL;

    if((fp = fopen("Sell_after_editing","wb"))==NULL){
        perror(NULL);
        exit(456);
    }

    for(nodeSell = headSell; nodeSell != NULL; nodeSell = nodeSell->next){
        if(fwrite(&nodeSell,sizeof(sAdvert_t),1,fp)!=1){
            perror(NULL);
            fclose(fp);
            exit(-2);
        }
    }
}


void printAllElements(sList_t *headReq, sList_t *headSell)
{
    sList_t *nodeReq = NULL;
    sList_t *nodeSell = NULL;

    for(nodeReq = headReq; nodeReq != NULL; nodeReq = nodeReq->next){
        printf("\n\n****Requested advert: ****\n\n");

        printf("Type:\t%s", nodeReq->payload.type);
        printf("ID:\t%s", nodeReq->payload.id);
        printf("Title:\t%s", nodeReq->payload.title);
        printf("Price:\t%lf", nodeReq->payload.price);
    }

    for(nodeSell = headSell; nodeSell != NULL; nodeSell = nodeSell->next){
        printf("\n\n****Selling advert: ****\n\n");

        printf("Type:\t%s", nodeSell->payload.type);
        printf("ID:\t%s", nodeSell->payload.id);
        printf("Title:\t%s", nodeSell->payload.title);
        printf("Price:\t%lf", nodeSell->payload.price);
    }
}

void freeList(sList_t *headReq, sList_t *headSell)
{
    for(;headReq != NULL; headReq = headReq->next){
        free(headReq);
    }

    for(;headSell != NULL; headSell = headSell->next){
        free(headSell);
    }
}
