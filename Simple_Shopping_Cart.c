// DS Course Project
// header files
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#define MAX 15
#define size 7
// structure declarations
struct node
{
    int data;
    char p[100];
    struct node *next;
};
typedef struct user
{
    char mail[100];
    char password[32];
    struct user *next;
} user;
typedef struct Cart
{
    long long int price_cart;
    char *product_name;
    struct Cart *next;
} cart;
typedef struct Product
{
    char *variant;
    long long int price;
    struct Product *next;
} product;
typedef struct Categories
{
    char *Category_name;
    struct Categories *left;
    struct Categories *right;
    struct Categories *LL_first;
} category;
// function declarations
void totalPrice_cart();
void category_operations();
void catsnext();
void show_cart(cart *);
void newuser(void);
int checkstrength(char *);
void olduser(void);
void userpage(void);
void exit_program();
void enqueue(user *);
void insert(int, char *);
user *userseach(char *);
// variable declarations
char temail[100];
user *front = NULL, *rear = NULL;
struct node *chain[size];
category *root = NULL, *stack[30];
product *first[MAX], *first_product = NULL, *last_product = NULL;
cart *stack2[30];
cart *first_cart = NULL, *last_cart = NULL;
int top = -1, c = 1, count_cart = 0, t2 = -1, cp = 0, flag_rewards = 0;
long long int total_cart = 0;
//  Users and Reviews
void in()
{
    int i;
    for (i = 0; i < size; i++)
        chain[i] = NULL;
}
user *usersearch(char *p)
{
    user *temp;
    temp = front;
    while (temp != NULL)
    {
        if (strcmp(temp->mail, p) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
void newuser()
{
    user *p, *temp;
    char *tpassword, *n;
    char email[32], password[32];
    printf("\n\t Enter email address:  ");
    fflush(stdin);
    scanf("%s", email);
    strcpy(temail, email);
    p = usersearch(temail);
    if (p != NULL)
    {
        printf("\n\t Email is already present\n");
        userpage();
        return;
    }
    printf("\n\t Enter password :  ");
    fflush(stdin);
    scanf("%s", password);
    tpassword = password;
    while (checkstrength(tpassword) != 1)
    {
        printf("\n\t Try again");
        printf("\n\t Type your password: ");
        fflush(stdin);
        scanf("%s", password);
        tpassword = password;
    }
    temp = (user *)malloc(sizeof(user));
    strcpy(temp->mail, temail);
    strcpy(temp->password, tpassword);
    enqueue(temp);
}
int checkstrength(char *string1)
{
    int i;
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;

    for (i = 0; i < strlen(string1); ++i)
    {

        if (islower(string1[i]))
            hasLower = true;
        if (isupper(string1[i]))
            hasUpper = true;
        if (isdigit(string1[i]))
            hasDigit = true;
    }
    if (hasLower && hasUpper && hasDigit)
    {
        printf("\n\t Strong Password\n");
        return 1;
    }
    else
    {
        printf("\n\t Weak Password\n");
        return 0;
    }
}
void olduser()
{

    int t = 0;
    user *p;
    char *tpassword;
    char email[32], password[32];
    printf("\n\t Enter email: ");
    fflush(stdin);
    scanf("%s", email);
    strcpy(temail, email);
    p = usersearch(temail);
    if (p == NULL)
    {
        printf("\n\t No logged in user\n");
        userpage();
        printf("\n");
        return;
    }
    printf("\n\t Enter password: ");
    fflush(stdin);
    scanf("%s", password);
    t = strcmp(password, p->password);
    // printf("%d",t);
    while (strcmp(password, p->password) != 0)
    {
        printf("\n\t Reach\n");
        if (strcmp(password, p->password) == 0)
        {
            break;
        }
        t++;
        printf("\n\t Enter password: ");
        fflush(stdin);
        scanf("%s", password);
        printf("\n\t Wrong Password Try again\n");
        if (t > 3)
        {
            userpage();
            break;
        }
    }
}
void enqueue(user *p)
{
    user *nn;
    nn = (user *)malloc(sizeof(user));
    strcpy(nn->mail, p->mail);
    strcpy(nn->password, p->password);
    nn->next = NULL;
    if (front == NULL)
    {
        front = nn;
        rear = nn;
        return;
    }
    rear->next = nn;
    rear = nn;
}
user *dequeue()
{
    user *n;
    if (front == NULL)
    {
        printf("\n\t Queue is empty\n");
    }
    n = front;
    if (front == rear)
    {
        front = NULL;
        rear = NULL;
    }
    else
    {
        front = front->next;
    }
    return n;
}
void display()
{
    user *temp;
    if (front == NULL)
        printf("\n\t Queue is empty\n");
    else
    {
        temp = front;
        while (temp != NULL)
        {
            printf("\n\t%s", temp->mail);
            temp = temp->next;
        }
    }
}
user *frontele()
{
    return front;
}
void userpage()
{
    int t;

    printf("\n\t 1.New user");
    printf("\n\t 2.Old user");
    printf("\t  Choice:  ");
    scanf("%d", &t);
    // printf("\n\t %d",t);
    if (t == 1)
        newuser();
    if (t == 2)
        olduser();
}
void init()
{
    user *temp, *input;
    struct node *in;
    int dummy;
    char m[100];
    FILE *fp, *f;
    fp = fopen("edockdata", "r");
    if (fp == NULL)
        printf("\n\t No user data");
    else
    {
        temp = (user *)malloc(sizeof(user));
        input = (user *)malloc(sizeof(user));
        while (fread(input, sizeof(user), 1, fp))
        {
            strcpy(temp->mail, input->mail);
            strcpy(temp->password, input->password);
            enqueue(temp);
        }
    }
    remove("edockdata");
    fclose(fp);
    f = fopen("reviewdata", "r");

    if (f == NULL)
        printf("\n\t No review data\n");
    else
    {
        in = (struct node *)malloc(sizeof(struct node));
        while (fread(in, sizeof(struct node), 1, fp))
        {

            dummy = in->data;
            strcpy(m, in->p);
            insert(dummy, m);
        }
    }
    remove("reviewdata");
    fclose(f);
}
void exit_program()
{
    int i;
    user *temp, *input1;
    struct node *dummy, *in;
    FILE *fp, *f;
    input1 = (user *)malloc(sizeof(user));
    fp = fopen("edockdata", "w");
    temp = front;
    while (temp != NULL)
    {
        strcpy(input1->mail, temp->mail);
        strcpy(input1->password, temp->password);
        fwrite(input1, sizeof(user), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
    f = fopen("reviewdata", "w");
    in = (struct node *)malloc(sizeof(struct node));
    for (i = 0; i < size; i++)
    {
        dummy = chain[i];
        while (dummy != NULL)
        {
            in->data = dummy->data;
            strcpy(in->p, dummy->p);
            fwrite(in, sizeof(struct node), 1, fp);
            dummy = dummy->next;
        }
    }
    fclose(f);
}
void rewards()
{
    user *m;
    m = frontele();

    if (strcmp(m->mail, temail) == 0)
    {
        // printf("\n\t Enter code 'mad' for discount of 5");
        m = dequeue();
        enqueue(m);
    }
    else
    {
        flag_rewards = 1;
        // printf("\n\t No rewards available");
    }
    m = frontele();
}
void insert(int value, char *m)
{
    int key;
    // create a newnode with value
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = value;
    strcpy(newNode->p, m);
    newNode->next = NULL;
    // calculate hash key
    key = value % size;
    // check if chain[key] is empty
    if (chain[key] == NULL)
        chain[key] = newNode;
    // collision
    else
    {
        // add the node at the end of chain[key].
        struct node *temp = chain[key];
        while (temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}
void print()
{
    int i;

    for (i = 0; i < size; i++)
    {
        struct node *temp = chain[i];
        printf("\n\t Reviews[%d]-->", i);
        while (temp)
        {
            printf(" %s--> ", temp->p);
            temp = temp->next;
        }
        printf(" End of reviews\n");
    }
}
void review()
{
    int t;
    int key;
    char m[100];
    printf("\n\t 1.Write a review on our app\n\t 2.See review given by other users\n");
    printf("\n\t Choice: ");
    scanf("%d", &t);
    if (t == 1)
    {
        printf("\n\t Give your rating between 1-5 for a product:  ");
        scanf("%d", &key);
        printf("\n\t Write your review on it: ");
        fflush(stdin);
        gets(m);
        insert(key, m);
    }
    if (t == 2)
    {
        print();
    }
}
// Carts, Categories, Checkout
void push_stack(category *add)
{
    stack[++top] = add;
}
category *pop_stack()
{
    return stack[top--];
}
void push_stack2(cart *add)
{
    stack2[++t2] = add;
}
cart *pop_stack2()
{
    return stack2[t2--];
}
product *new_product(char *name, long long int cost)
{
    product *new_pro;
    new_pro = (product *)malloc(sizeof(product));
    new_pro->variant = (char *)malloc(strlen(name) + 1);
    strcpy(new_pro->variant, name);
    // new_pro->variant=name;
    new_pro->price = cost;
    new_pro->next = NULL;
    return new_pro;
}
category *new_category(char *name)
{
    category *new_cat;
    new_cat = (category *)malloc(sizeof(category));
    new_cat->Category_name = (char *)malloc(strlen(name) + 1);
    strcpy(new_cat->Category_name, name);
    // new_cat->Category_name=name;
    // printf("%s",new_cat->Category_name);
    new_cat->left = NULL;
    new_cat->right = NULL;
    new_cat->LL_first = NULL;
    return new_cat;
}
void addtoCart(cart *item)
{
    cart *new_cartitem;
    new_cartitem = (cart *)malloc(sizeof(cart));
    new_cartitem->product_name = (char *)malloc(strlen(item->product_name) + 1);
    strcpy(new_cartitem->product_name, item->product_name);
    // new_cartitem->product_name = item->product_name;
    new_cartitem->price_cart = item->price_cart;
    total_cart += new_cartitem->price_cart;
    new_cartitem->next = NULL;
    if (first_cart == NULL && last_cart == NULL)
    {
        first_cart = new_cartitem;
        last_cart = new_cartitem;
    }
    else
    {
        last_cart->next = new_cartitem;
        last_cart = last_cart->next;
    }
    count_cart++;
}
void deletefromCart()
{
    cart *temp, *t;
    int position, i, choice_cart;
    if (count_cart == 0)
    {
        printf("\n\t No cart items to delete\n");
        return;
    }
    if (count_cart != 0)
    {
        printf("\n\t Present Cart items are: ");
        show_cart(first_cart);
    }
    printf("\n");
    printf("\t Enter your chocie: ");
    scanf("%d", &choice_cart);
    position = count_cart - (choice_cart - 1);
    if (position <= count_cart && position > 0 && count_cart != 0)
    {
        if (position == count_cart && count_cart != 1)
        {
            temp = first_cart;
            while (temp->next->next != NULL)
                temp = temp->next;
            t = temp->next;
            temp->next = NULL;
        }
        else if (position == count_cart && count_cart == 1)
        {
            t = first_cart;
            first_cart = NULL;
            last_cart = NULL;
        }
        else if (position == 1)
        {
            t = first_cart;
            first_cart = first_cart->next;
        }
        else
        {
            temp = first_cart;
            i = 1;
            while (i < position - 1)
            {
                temp = temp->next;
                i++;
            }
            t = temp->next;
            temp->next = temp->next->next;
        }
        total_cart = total_cart - t->price_cart;
        free(t);
        printf("\n\t Your Cart item has been deleted");
        count_cart--;
    }
    else
    {
        printf("\n\t Cart item not present to delete \n");
        totalPrice_cart();
    }
    if (first_cart != NULL)
    {
        printf("\n\t Present Cart is: ");
        show_cart(first_cart);
    }
}
void totalPrice_cart()
{
    double price = (double)total_cart;
    printf("\n\t Your subtotal is Rs.%0.2lf", price);
}
void show_cart(cart *first_cart)
{
    cart *temp;
    int c_cart = 0;
    temp = first_cart;
    if (count_cart != 0)
    {
        while (temp != NULL)
        {
            push_stack2(temp);
            temp = temp->next;
        }
        while (t2 >= 0)
        {
            temp = pop_stack2();
            printf("\n\t %d. %s  Rs.%lld", ++c_cart, temp->product_name, temp->price_cart);
        }
        totalPrice_cart();
    }
    else
        printf("\n\t No item to show");
}
void category_names()
{
    category *temp;
    product *templ;
    root = new_category("Category");
    root->left = new_category("Mobiles");
    root->left->left = new_category("iOS");
    root->left->left->left = new_category("iPhone X");
    root->left->left->right = new_category("iPhone 11");
    root->left->right = new_category("Android");
    root->left->right->left = new_category("Google");
    root->left->right->right = new_category("Samsung");
    root->left->right->left->left = new_category("Pixel 3");
    root->left->right->left->right = new_category("Pixel 4");
    root->left->right->right->left = new_category("Samsung Galaxy Note");
    root->left->right->right->right = new_category("Samsung Galaxy S ");
    root->right = new_category("Laptops");
    root->right->left = new_category("Mac");
    root->right->left->left = new_category("MacBook Pro");
    root->right->left->right = new_category("MacBook Air");
    root->right->right = new_category("PC");
    root->right->right->left = new_category("Dell");
    root->right->right->right = new_category("Razer");
    first[c++] = new_product("iPhone Xs 256GB", 74999);
    root->left->left->left->LL_first = (category *)first[c - 1];
    first[c - 1]->next = new_product("iPhone Xs Max 256GB", 99999);
    first[c++] = new_product("iPhone 11", 59999);
    root->left->left->right->LL_first = (category *)first[c - 1];
    first[c - 1]->next = new_product("iPhone 11 Pro 256GB", 89999);
    first[c - 1]->next->next = new_product("iPhone 11 Pro Max 256GB", 120000);
    first[c++] = new_product("Pixel 3 128GB", 69999);
    root->left->right->left->left->LL_first = (category *)first[c - 1];
    first[c - 1]->next = new_product("Pixel 3 XL 128GB", 84999);
    first[c - 1]->next->next = new_product("Pixel 3a 64GB", 34999);
    first[c - 1]->next->next->next = new_product("Pixel 3a XL 128GB", 45999);
    first[c++] = new_product("Pixel 4a 128GB", 24999);
    root->left->right->left->right->LL_first = (category *)first[c - 1];
    first[c - 1]->next = new_product("Pixel 4a XL 128GB", 34999);
    first[c++] = new_product("Samsung Galaxy Note 10 256GB", 69999);
    root->left->right->right->left->LL_first = (category *)first[c - 1];
    first[c - 1]->next = new_product("Samsung Galaxy Note 10+ 256GB", 94999);
    first[c++] = new_product("Samsung Galaxy S20", 59999);
    root->left->right->right->right->LL_first = (category *)first[c - 1];
    first[c - 1]->next = new_product("Samsung Galaxy S20+", 74999);
    first[c - 1]->next->next = new_product("Samsung Galaxy S20 Ultra", 99999);
    first[c++] = new_product("MacBook Pro 13-inch i7 10th-Gen 2020", 139999);
    root->right->left->left->LL_first = (category *)first[c - 1];
    first[c - 1]->next = new_product("MacBook Pro 17-inch i9 10th-Gen 2020", 189999);
    first[c++] = new_product("MacBook Air 13-inch i5 10th-Gen 2019", 89999);
    root->right->left->right->LL_first = (category *)first[c - 1];
    first[c - 1]->next = new_product("MacBook Air 15-inch i5 10th-Gen 2019", 109999);
    first[c++] = new_product("Dell Xps 13-inch i7 10th-Gen 2020", 99999);
    root->right->right->left->LL_first = (category *)first[c - 1];
    first[c++] = new_product("Razer Blade 14 HD Gaming Laptop (7th Gen Intel Core i7, 16GB RAM, 512GB SSD)", 139999);
    root->right->right->right->LL_first = (category *)first[c - 1];
}
int count_LL(product *templ)
{
    product *temp;
    int c = 0;
    temp = templ;
    while (temp != NULL)
    {
        c++;
        temp = temp->next;
    }
    return c;
}
product *choiceInLL(int choicell, product *temp)
{
    int ch;
    product *temp2;
    temp2 = temp;
    ch = 1;
    if (ch == choicell)
        return temp2;
    while (1)
    {
        temp2 = temp2->next;
        ch++;
        if (ch == choicell)
            break;
    }
    return temp2;
}
product *display_LL(product *templ)
{
    int count = 1, c, choicell;
    product *temp2, *temp3;
    temp2 = templ;
    temp3 = templ;
    c = count_LL(temp2);
    printf("\n");
    while (temp2 != NULL && count <= c)
    {
        printf("\t %d. %s  for Rs.%lld \n", count++, temp2->variant, temp2->price);
        temp2 = temp2->next;
    }
    printf("\n\t Choice: ");
    scanf("%d", &choicell);
    while (1)
    {
        if (choicell > c)
        {
            printf("\n\t Please Enter your choice correctly!\n");
            printf("\n\t Choice: ");
            scanf("%d", &choicell);
        }
        else if (choicell <= c)
            break;
    }
    temp3 = choiceInLL(choicell, temp3);
    printf("\n");
    return temp3;
}
void option_cart(product *temp2)
{
    int i = 0, choice;
    cart *t;
    char s[200], *str = NULL;
    printf("\t Do you want to add this to cart? (0 to exit, 1 for Add to Cart, 2 to go to Mainpage):  ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        t = (cart *)malloc(sizeof(cart));
        t->price_cart = temp2->price;
        if (str == NULL)
            str = malloc(sizeof(char) * strlen(temp2->variant));
        strcpy(s, temp2->variant);
        while (s[i] != '\0')
        {
            str[i] = s[i];
            i++;
        }
        str[i] = '\0';
        t->product_name = str;
        addtoCart(t);
        show_cart(first_cart);
        printf("\n");
    }
    else if (choice == 0)
        exit(0);
    else if (choice == 2)
        return;
    else
    {
        printf("\n\t Please Enter correct choice! \n");
        return;
    }
}
void category_operations()
{
    category *temp;
    int choice;
    product *templ, *temp2;
    temp = root;
    printf("\n");
    while (temp->left != NULL && temp->right != NULL)
    {
        printf("\t Select your %s from the following: \n", temp->Category_name);
        printf("\t 1. %s\n\t 2. %s", temp->left->Category_name, temp->right->Category_name);
        printf("\t Choice: ");
        scanf("%d", &choice);
        printf("\n");
        if (choice == 1)
            temp = temp->left;
        else if (choice == 2)
            temp = temp->right;
        else
            printf("\n\t Please Enter your choice correctly!\n");
    }
    temp = temp->LL_first;
    templ = (product *)temp;
    temp2 = display_LL(templ);
    printf("\n");
    option_cart(temp2);
}
void check_out()
{
    char option[4], coupon[5];
    int counter = 1, choice;
    if (flag_rewards == 0)
    {
        printf("\n\t Do you want to enter a coupon code? (Yes or No):  ");
        fflush(stdin);
        scanf("%[^\n]", option);
        if (strcmp(option, "Yes") == 0)
        {
            while (1)
            {
                printf("\n\t Please Enter your coupon code:  ");
                fflush(stdin);
                scanf("%[^\n]", coupon);
                if (strcmp(coupon, "mad") == 0)
                {
                    printf("\n\t Congratulations! You have been granted a 5 percent offer on your grand total");
                    total_cart = (double)(total_cart - (total_cart * 5) / 100);
                    break;
                }
                else
                {
                    printf("\n\t Sorry, this coupon code is wrong");
                    printf("\n\n\t Do you want to try again? (0 for No, 1 for Yes) : ");
                    scanf("%d", &choice);
                    if (choice == 0)
                        break;
                    else if (choice == 1 && counter <= 3)
                        counter++;
                    else if (choice == 1 && counter > 3)
                    {
                        printf("\n\t You have exhausted your chances");
                        break;
                    }
                }
            }
        }
    }
    else if (flag_rewards == 1)
        printf("\n\t No rewards");
    totalPrice_cart();
    printf("\n\t Your order has been placed!\n\t Our Offline team will contact you in the next 24 hours\n ");
}
void add_product(product *item)
{
    product *new_proitem;
    new_proitem = (product *)malloc(sizeof(product));
    new_proitem->variant = (char *)malloc(strlen(item->variant) + 1);
    strcpy(new_proitem->variant, item->variant);
    new_proitem->price = item->price;
    new_proitem->next = NULL;
    if (first_product == NULL && last_product == NULL)
    {
        first_product = new_proitem;
        last_product = new_proitem;
    }
    else
    {
        last_product->next = new_proitem;
        last_product = last_product->next;
    }
    cp++;
}
void quick_search()
{
    product *temp, *temp2;
    int pc = 1, i = 0, choice;
    char *result, s[100], *searchstring;
    printf("\n\t Enter Search string: ");
    searchstring = malloc(sizeof(char) * 15);
    fflush(stdin);
    scanf("%[^\n]", searchstring);
    while (pc <= c)
    {
        temp = first[pc];
        while (temp != NULL)
        {
            strcpy(s, temp->variant);
            result = strstr(s, searchstring);
            if (searchstring[0] == s[0])
                if (result != NULL)
                    add_product(temp);
            temp = temp->next;
        }
        pc++;
    }
    if (first_product != NULL)
    {
        printf("\n\t Your search results are: ");
        printf("\n\t");
        temp2 = first_product;
        while (temp2 != NULL)
        {
            printf("\n\t %d. %s for Rs.%lld", ++i, temp2->variant, temp2->price);
            temp2 = temp2->next;
        }
        printf("\n");
        printf("\n\t Choice: ");
        scanf("%d", &choice);
        i = 1;
        temp2 = first_product;
        while (1)
        {
            if (i == choice)
                break;
            temp2 = temp2->next;
            i++;
        }
        printf("\n");
        option_cart(temp2);
        while (first_product != NULL)
        {
            temp = first_product;
            pc--;
            first_product = first_product->next;
            free(temp);
        }
        first_product = NULL;
        last_product = NULL;
        pc = 1;
    }
    else if (first_product == NULL)
        printf("\n\t No results");
}
int main()
{
    int t, option, flag = 0;
    user *x;
    category_names();
    printf("\n\t ---------Welcome to Amazon Shopping---------");
    printf("\n");
    in();
    init();
    userpage();
    rewards();
    if (flag_rewards == 0)
        printf("\n\t Enter code 'mad' for a discount of 5 percent\n");
    printf("\n\t Successful\n");
    do
    {
        printf("\n\n\t What would you like to do? : \n");
        printf("\n\t 1.Browse for products\n\t 2.Show cart\n\t 3.Delete an Item from Cart\n\t 4.Continue to Checkout\n\t 5.Quick search\n\t 6.Reviews\n\t 7.Exit\n");
        printf("\n\t Choice: ");
        scanf("%d", &option);
        if (option == 1)
            category_operations();
        else if (option == 2)
            show_cart(first_cart);
        else if (option == 3)
            deletefromCart();
        else if (option == 4)
        {
            if (total_cart == 0)
                printf("\n\t Your cart is empty..Please add some Products to continue\n");
            else
            {
                check_out();
                flag = 1;
            }
            if (flag == 1)
                break;
        }
        else if (option == 5)
            quick_search();
        else if (option == 6)
            review();
    } while (option != 7);
    exit_program();
    printf("\n\t Thanks for shopping with us!");
    printf("\n");
    return 0;
}
