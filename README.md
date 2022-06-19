# Simple-Shopping-Cart
Using C language &amp; relevant data structures we have implemented a shopping cart interface where we can see the products, search the products, add them to cart, and also delete them from the cart. 

**The main functions of our project are:**

1. **Selecting products from the categories.**
2. **Adding products to cart and deleting them from cart.**
3. **Display Cart items.**
4. **Add reviews for the application.**
5. **Login with your user id and password.**
6. **Get rewards.**
7. **Quickly search through the inventory.**
8. **Go to checkout to order the product.**


Selecting products from the categories.

- Here, we will be displaying the categories which are Mobiles and Laptops from which the user can choose the products going through the categories.
- The Data Structures used are Binary tree &amp; Linked list.
- We have used Binary tree to display categories, here the user is given a choice between the two categories. After the selection is over, the relevant products are displayed from which the user can choose what to do.

Adding products to cart and deleting them from cart.

- Users can add products to the cart or delete existing products from the cart.
- The Data Structure used is Linked List.
- Adding products to the cart happens after the products are displayed and deleting them can be performed if the cart has some products in it.

Displaying Cart Items.
  - This function is to show the products which are present in the cart.
  - The Data structures used are Linked list and Stacks.

Add reviews to the application.
  - This allows you to add a review and view the other&#39;s reviews about the application. It also stores the user reviews in a file locally.
  - The Data structure used is Dictionary.

Login with user id and password.
  - This allows you to create your account/ login to your account if it already exists.
  - The Data Structure used is Queue.
  - The new user function takes in email id and password from the user. It checks if the user is present already and also the strength of the password, if everything&#39;s good it enqueues it into a queue which stores them in a file locally. The old user function also takes in user id and password and checks for the user, if found logs him in.

Get Rewards.
  - Rewards are given to the user who logs in first.
  - The data structure is Queue.

Quickly search through the inventory.
  - This allows user to quickly search through the products available by keywords like &#39;iph&#39; shows the list with iphones, &#39;pix&#39; shows the list with pixel.
  - The data structure used is Linked List.

Go to Checkout to order the product.
  - This will show the subtotal of your cart with or without the coupon and the user can buy the product here.
