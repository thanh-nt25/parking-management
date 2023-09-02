#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "libs/bst_traversal.h"

#define OPTIONS 8 // CHỈNH SỬA OPTIONS
// #define NUM_LINE 1000 // SỐ TRƯỜNG THỰC THỂ DỮ LIỆU

#define MAX_WORDS 20 // DÙNG CHO HÀM TÁCH CHUỖI
#define MAX_CAR 300

typedef struct node_s {
    data_t data; // tao mot thuc te cua kieu cau truc data
    struct node_s *next;
}   node_t, *root_t;

node_t* CreateNewNode (const data_t data)
{
    // tao ra va ko chua thong tin
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if(new_node == NULL) return NULL;

    // truyen du lieu va gan phan tu tiep theo = NULL
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

root_t llInsertHead(root_t root, const data_t data)
{
    node_t *pNewNode = CreateNewNode(data);
    (pNewNode -> next) = root;
    return (root_t)pNewNode;
}

// ham gan root ban dau = NULL
root_t llInit() { return NULL; }

root_t llDeleteAll(root_t root) {
  node_t* p = NULL;
  for (; root != NULL; root = p) {
    p = root->next;
    free(root);
  }
  return NULL;
}

root_t llprintf(root_t root)
{
    for(node_t* p = root; p != NULL; p = p->next) showData(p -> data);
    printf("\n");
    return root;
}

int llFind_ra(root_t root, int YYYY, int MM, int DD){
    root_t search = root;
    int take=0;
    while (search != NULL)
    {
        if (search->data.time.DD == DD &&
        search->data.time.MM == MM &&
        search->data.time.YYYY == YYYY && 
        search->data.take_io == 1) take = take +1;
        search = search -> next;
    }
    return take;
}

int llFind_gui(root_t root, int YYYY, int MM, int DD){
    root_t search = root;
    int take=0;
    while (search != NULL)
    {
        if (search->data.time.DD == DD &&
        search->data.time.MM == MM &&
        search->data.time.YYYY == YYYY && search->data.take_io == 0) take = take +1;
        search = search -> next;
    }
    return take;
}

/* ===============================================================*/
/* ======================= Tiền xử lí ===========================*/

int count_line(FILE *fp, char *file_name){
    int count = 0;
    char ch;
    if ((fp = fopen(file_name, "r+")) == NULL) return -1;
    do{
        ch = fgetc(fp);
        if(ch == '\n') count++;
    }   while(ch != EOF);
    return count;
}

// thay thế \n trong con trỏ chuỗi = \0
void reWrite(char *word){
    int i=0;
    while(*(word+i) != '\n'){ // *(word+i) != '\r' 
        ++i;
    }
    *(word + i) = '\0';
}

// ko đếm được với con trỏ chuỗi
int word_count(char *sen){
    int count=0;
    for (int i=0; sen[i] != '\0'; ++i){
        if (sen[i] == ' ' || sen[i] == '\n') count++;
    }
    count++;
    return count;
}

char* to_single_lowcase(char *word){
    char *low_case = malloc(sizeof(word));
    for(int i=0; word[i] != '\0'; ++i ){
        low_case[i] = tolower(word[i]);
    }
    return low_case;
}

char* to_single_upcase(char *word){
    char *up_case = malloc(sizeof(word));
    for(int i=0; word[i] != '\0'; ++i ){
        up_case[i] = toupper(word[i]); 
    }
    return up_case;
}


// thay thế MAX_WORDS bằng số từ trong câu => trả lại con trỏ đến đầu chuỗi lưu trữ
// char *words = split_sentence(sen);
char **split_sentence(char *sentence) {
    // con tro luu dia chi cua con tro den chuoi can modi =)))
    char **words = malloc(MAX_WORDS * sizeof(char*)); 
    int i = 0;

    char *word = strtok(sentence, " ");
    while (word != NULL && i < MAX_WORDS) {
        words[i] = to_single_lowcase(word);
        i++;
        word = strtok(NULL, " ");
    }
    return words;
}

/* nhập chuỗi bằng hàm fgets
fflush(stdin);
fgets(str, sizeof(str), stdin);
str[strcspn(str, "\n")] = '\0';
*/

// scanf("%[^\n]%*c", sen);

int NBr_Car(){
    FILE *fp = fopen("log_input.txt", "r");
    int NBrCar = count_line(fp, "log_input.txt" );
    return NBrCar;
}

/* ==================================================================*/
/* ================================= MENU ===========================*/ 
/* =================================================================*/

void menuprintf(){
    printf("==========================\n");
    printf("Choung trinh quan ly bai xe\n");
    printf("Vui long chon mot trong cac chuc nang sau:\n");
    printf("1. Doc du lieu tu file log\n");
    printf("2. Tra cuu so luong xe gui/lay theo ngay trong qua khu\n");
    printf("3. Thong tin cac xe trong bai hien tai\n");
    printf("4. Gui them xe moi\n");
    printf("5. Tra xe\n");
    printf("6. Cap nhat log du lieu\n");
    printf("7. Luu danh sach xe dang co trong bai ra file\n");
    printf("8. Exit\n");
    printf("==========================\n");
}

int check_choice(){
        int choice;
        do{
            printf("\nLua chon cua ban la:\n");
            menuprintf();
            scanf("%d", &choice);
            fflush(stdin);
            if(choice < 1 || choice > OPTIONS) printf("Please enter the number from 1 to %d!\n", OPTIONS);
        }while(choice < 1 || choice > OPTIONS);
        return choice;
}

/* ====================================================================*/
/* ===================== Các hàm trong Menu ==========================*/ 
/* ==================================================================*/

root_t mot_(root_t root, data_t *trans){
    printf("1st function\n");
    // chuyển dữ liệu => data structure => BST
    // YOUR CODE
    int NUM_CAR = NBr_Car();
    FILE * fp = fopen("log_input.txt", "r");
    int i=0;
    while(  fscanf(fp, "%d-%d-%d %d:%d:%d %s %d", 
    &trans[i].time.YYYY, &trans[i].time.MM, &trans[i].time.DD, 
    &trans[i].time.hh, &trans[i].time.mm, &trans[i].time.ss,
    trans[i].bien_so, &trans[i].take_io) != EOF )        {
        // reWrite(&trans[i].bien_so);
        ++i;
    }
    printf("Read Successfully!\n");
    for(int i=0; i < NUM_CAR ; i++)
        root = llInsertHead(root, trans[i]);
    llprintf(root);
    return root;
}

void hai_(root_t lst){
    printf("2nd function\n");
    // YOUR CODE
    data_t print;
    printf("nam:");
    scanf("%d", &print.time.YYYY);
    fflush(stdin);
    printf("thang:");
    scanf("%d", &print.time.MM);
    fflush(stdin);
    printf("ngay:");
    scanf("%d", &print.time.DD);
    fflush(stdin);
    int ra = 0;
    int gui = 0;
    ra = llFind_ra(lst, print.time.YYYY, print.time.MM, print.time.DD);
    gui = llFind_gui(lst, print.time.YYYY, print.time.MM, print.time.DD);
    printf("So luong xe gui: %d\n", gui);
    printf("So luong xe ra: %d\n", ra);

}

void ba_(tree_t *tree, data_t *trans_tree){
    printf("3rd function\n");
    // YOUR CODE
    int NUM_CAR = NBr_Car();
    FILE *fp = fopen("log_input.txt", "r");
    // for(int i=0; i < NUM_CAR; ++i){
    //     strcpy( trans_tree[i].bien_so, trans[i].bien_so);
    //     trans_tree[i].take_io = trans[i].take_io;
    //     trans_tree[i].time.DD = trans[i].time.DD;
    //     trans_tree[i].time.hh = trans[i].time.hh;
    //     trans_tree[i].time.MM = trans[i].time.MM;
    //     trans_tree[i].time.mm = trans[i].time.mm;
    //     trans_tree[i].time.ss = trans[i].time.ss;
    //     trans_tree[i].time.YYYY = trans[i].time.YYYY;
    // }
    int i=0;
    while(  fscanf(fp, "%d-%d-%d %d:%d:%d %s %d", 
    &trans_tree[i].time.YYYY, &trans_tree[i].time.MM, &trans_tree[i].time.DD, 
    &trans_tree[i].time.hh, &trans_tree[i].time.mm, &trans_tree[i].time.ss,
    trans_tree[i].bien_so, &trans_tree[i].take_io) != EOF )        {
        // reWrite(&trans[i].bien_so);
        ++i;
    }
    
    for(int i=0; i < NUM_CAR; ++i){
            insertNode(trans_tree[i], tree);
    }
    printf("So luong xe hien co: %d\n", NUM_CAR);
    iter_inorder(*tree);
    fclose(fp);
}



void bon_(tree_t tree, data_t *trans_tree, data_t *trans){
    printf("4st function\n");
    // YOUR CODE
        time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // printf("%d\n", tm.tm_year+1990);

    char bien_so_xe[13];
    printf("nhap bien so xe can gui:\n");
    scanf("%s", bien_so_xe);

    if (search(bien_so_xe, tree) != NULL) printf("Loi: Xe co trong bai\n");
    else{
    data_t tmp;
        strcpy( tmp.bien_so, bien_so_xe);
        tmp.take_io = 1;
        tmp.time.YYYY = tm.tm_year + 1900;
        tmp.time.MM = tm.tm_mon+1;
        tmp.time.DD = tm.tm_mday;
        tmp.time.hh = tm.tm_hour;
        tmp.time.mm = tm.tm_min;
        tmp.time.ss = tm.tm_sec;
    FILE* fp = fopen("log_input.txt", "a");
    fprintf(fp, "%02d-%02d-%02d %02d:%02d:%02d %s %d\n", 
    tmp.time.YYYY, tmp.time.MM, tmp.time.DD, 
    tmp.time.hh, tmp.time.mm, tmp.time.ss,
    tmp.bien_so, tmp.take_io);

    FILE* fch = fopen("change_log.txt", "a+");
    fprintf(fch, "%02d-%02d-%02d %02d:%02d:%02d %s %d\n", 
    tmp.time.YYYY, tmp.time.MM, tmp.time.DD, 
    tmp.time.hh, tmp.time.mm, tmp.time.ss,
    tmp.bien_so, tmp.take_io);

    printf("da them bien so xe can gui\n");
    fclose(fp);
    fclose(fch);
    }
}

void nam_(tree_t tree, data_t *trans_tree, data_t *trans){
    printf("5st function\n");
    // YOUR CODE
        time_t t = time(NULL);
    struct tm tm = *localtime(&t);

        char bien_so_xe_tra[13];
    printf("nhap bien so xe can tra:\n");
    scanf("%s", bien_so_xe_tra);
    if (search(bien_so_xe_tra, tree) == NULL) printf("Loi: Xe khong co trong bai\n");
    else{
    data_t tmp;
        strcpy( tmp.bien_so, bien_so_xe_tra);
        tmp.take_io = 0;
        tmp.time.YYYY = tm.tm_year + 1900;
        tmp.time.MM = tm.tm_mon+1;
        tmp.time.DD = tm.tm_mday;
        tmp.time.hh = tm.tm_hour;
        tmp.time.mm = tm.tm_min;
        tmp.time.ss = tm.tm_sec;
    FILE* fp = fopen("log_input.txt", "a");
    fprintf(fp, "%02d-%02d-%02d %02d:%02d:%02d %s %d\n", 
    tmp.time.YYYY, tmp.time.MM, tmp.time.DD, 
    tmp.time.hh, tmp.time.mm, tmp.time.ss,
    tmp.bien_so, tmp.take_io);

    FILE *fch = fopen("change_log.txt", "a+");
    fprintf(fch, "%02d-%02d-%02d %02d:%02d:%02d %s %d\n", 
    tmp.time.YYYY, tmp.time.MM, tmp.time.DD, 
    tmp.time.hh, tmp.time.mm, tmp.time.ss,
    tmp.bien_so, tmp.take_io);

    printf("da them bien so xe can tra\n");
    fclose(fp);
    fclose(fch);
    }
}

void sau_(){
    printf("6st function\n");
            printf("da them vao change_log.txt");
    // YOUR CODE
}

void bay_(){
    printf("7st function\n");
    // YOUR CODE
}

/* ===============================================================*/
/* ============================ Main =============================*/ 
/* ===============================================================*/

// int main(int argc, char *argv[])
int main(void){
    FILE *fp = NULL;
    FILE *fch = NULL;
    char *file_open = "log_input.txt"; // CHINH SUA TEN FILE DATA

    // int NUM_LINE = count_line(fp, file_open);
    
    root_t lst = llInit();


    tree_t tree = NULL;
    data_t trans[MAX_CAR]; // CHỈNH THEO TÊN (LƯU TRỮ DATA)
    data_t trans_tree[MAX_CAR];

    int choice = 0;
    do{
        choice = check_choice();
        switch (choice)
        {
        case 1:
            lst = mot_(lst,trans);
            break;
        case 2:
            hai_(lst);
            break;
        case 3:
            ba_(&tree, trans_tree);
            break;
        case 4:
            bon_(tree, trans_tree, trans);
            break;
        case 5:
            nam_(tree, trans_tree, trans);
            break;
        case 6:
            sau_();
            break;
        case 7:
            bay_();
            break;
        case 8:
            break;
        }
    }   while (choice != OPTIONS);


    lst = llDeleteAll(lst);
    freeTree(tree);
    // GIAI PHONG BO NHO
    return 0;
}