#include<string>
#include<iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

struct node{
   int left;
   int right;
   int use_other_balance_left;
   int use_other_balance_right;
   int add_to_left;
   int add_to_right;
   int total_weight;
   node *next;
};

int main()
{
   int num_of_balances, num_of_balances_2;
   int left_balance[2], right_balance[2], first_node = 0;
   node *root, *curr, *curr2;//curr2 digunakan pada saat looping pengelolaan data
   string str_left, str_right;
   cin>>num_of_balances;
   num_of_balances_2 = num_of_balances;//digunakan untuk pengolahan tiap node
   
   while(num_of_balances != 0)
   {
      int left_balance[2] = {0,0}, right_balance[2] = {0,0}, left_count = 0, right_count=0, k;
      string str_left_balance[2], str_right_balance[2];
      cin.clear();//harus pakai ini
      cin.sync();//kalau tidak, waktu tekan enter langsung kembali ke while. str_right di skip
      getline(cin, str_left);
      getline(cin, str_right);
      
      stringstream ssin_left(str_left);
      stringstream ssin_right(str_right);
      
      //LEFT BALANCE
      while (ssin_left.good() && left_count < 2)
      {
        ssin_left >> str_left_balance[left_count];
        left_count++;
      }
      
      left_balance[0] = atoi(str_left_balance[0].c_str());
      
      if(str_left_balance[1]=="")left_balance[1]=-1;
      else left_balance[1] = atoi(str_left_balance[1].c_str());
      
      //RIGHT BALANCE
      while (ssin_right.good() && right_count < 2)
      {
        ssin_right >> str_right_balance[right_count];
        right_count++;
      }
      
      right_balance[0] = atoi(str_right_balance[0].c_str());
      
      if(str_right_balance[1]=="")right_balance[1]=-1;
      else right_balance[1] = atoi(str_right_balance[1].c_str());
      
      if(first_node == 0)
      {
         root = new node;
         root->next = 0;
         root->left = left_balance[0];
         root->use_other_balance_left = left_balance[1];
         root->right = right_balance[0];
         root->use_other_balance_right = right_balance[1];
         first_node++;
      }
      else
      {
         curr = root;
         if(curr != 0)
         {
           while(curr->next !=0)
           {
             curr = curr->next;
           }
         }
         curr->next = new node;
         curr = curr->next;
         curr->next = 0;
         curr->left = left_balance[0];
         curr->use_other_balance_left = left_balance[1];
         curr->right = right_balance[0];
         curr->use_other_balance_right = right_balance[1];
      }
      
      num_of_balances--;
   }
   
   for(int a = num_of_balances_2; a>0;a--)//kerjain dari paling belakang
   {
      int stop_node = 0;
      int balance_diff = 0;
      curr = root;
      if(curr!=0)
      {
        while(curr->next!=0)
        {
           stop_node++;
           if(a == stop_node)break;
           curr=curr->next;//harus tempatin paling BAWAH!
        }
        //jika 2 2 nya tidak pake other balance
        if(curr->use_other_balance_left == -1 && curr->use_other_balance_right == -1)
        {
           balance_diff = curr->right - curr->left;
           if(balance_diff == 0)
           {
              curr->total_weight = 10 + curr->left + curr->right;
              curr->add_to_left = 0;
              curr->add_to_right = 0;
           }
           else
           {
              if(balance_diff<0)//jika KIRI lebih berat
              {
                 curr->add_to_right = balance_diff*-1;
                 curr->add_to_left = 0;
                 curr->total_weight =  10 + curr->left + curr->right + curr->add_to_right;
              }
              else if(balance_diff>0)//jika KANAN lebih berat
              {
                 curr->add_to_left = balance_diff;
                 curr->add_to_right = 0;
                 curr->total_weight =  10 + curr->left + curr->right + curr->add_to_left;
              }
           }
           
        }
        //jika yang KIRI pake other balance, dan yang KANAN tidak
        else if(curr->use_other_balance_left != -1 && curr->use_other_balance_right == -1)
        {
           int counter_left_use_other = 0;//hitung mundur. Karena balance 0 ada di paling akhir
           if(curr->use_other_balance_left<num_of_balances_2)
           {
              curr2=root;
              if(curr2!=0)
              {
                 while(curr2->next != 0)
                 {
                    counter_left_use_other++;
                    if(counter_left_use_other-1 == curr->use_other_balance_left)break;
                    curr2=curr2->next;
                 }
              }
              curr->left = curr->left + curr2->total_weight;
              
              balance_diff = curr->right - curr->left;
              if(balance_diff == 0)
              {
                curr->total_weight = 10 + curr->left + curr->right;
                curr->add_to_left = 0;
                curr->add_to_right = 0;
              }
              else
              {
                if(balance_diff<0)//jika KIRI lebih berat
                {
                  curr->add_to_right = balance_diff*-1;
                  curr->add_to_left = 0;
                  curr->total_weight =  10 + curr->left + curr->right + curr->add_to_right;
                }
                else if(balance_diff>0)//jika KANAN lebih berat
                {
                  curr->add_to_left = balance_diff;
                  curr->add_to_right = 0;
                  curr->total_weight =  10 + curr->left + curr->right + curr->add_to_left;
                }
              }
           }
           else if(curr->use_other_balance_left>=num_of_balances_2)//jika mau balance yg ga ada
           {                                                //hitung seperti tidak ada tambahan balance                       
              balance_diff = curr->right - curr->left;
              if(balance_diff == 0)
              {
                curr->total_weight = 10 + curr->left + curr->right;
                curr->add_to_left = 0;
                curr->add_to_right = 0;
              }
              else
              {
                if(balance_diff<0)//jika KIRI lebih berat
                {
                  curr->add_to_right = balance_diff*-1;
                  curr->add_to_left = 0;
                  curr->total_weight =  10 + curr->left + curr->right + curr->add_to_right;
                }
                else if(balance_diff>0)//jika KANAN lebih berat
                {
                  curr->add_to_left = balance_diff;
                  curr->add_to_right = 0;
                  curr->total_weight =  10 + curr->left + curr->right + curr->add_to_left;
                }
              } 
           }
           break;
        }
        //jika yang KANAN pake other balance, dan yang KIRI tidak
        else if(curr->use_other_balance_left == -1 && curr->use_other_balance_right != -1)
        {
           int counter_right_use_other = 0;//hitung mundur. Karena balance 0 ada di paling akhir
           if(curr->use_other_balance_right<num_of_balances_2)
           {
              curr2=root;
              if(curr2!=0)
              {
                 while(curr2->next != 0)
                 {
                    counter_right_use_other++;
                    if(counter_right_use_other-1 == curr->use_other_balance_right)break;
                    curr2=curr2->next;
                 }
              }
              curr->right = curr->right+curr2->total_weight;
              
              balance_diff = curr->right - curr->left;
              if(balance_diff == 0)
              {
                curr->total_weight = 10 + curr->left + curr->right;
                curr->add_to_left = 0;
                curr->add_to_right = 0;
              }
              else
              {
                if(balance_diff<0)//jika KIRI lebih berat
                {
                  curr->add_to_right = balance_diff*-1;
                  curr->add_to_left = 0;
                  curr->total_weight =  10 + curr->left + curr->right + curr->add_to_right;
                }
                else if(balance_diff>0)//jika KANAN lebih berat
                {
                  curr->add_to_left = balance_diff;
                  curr->add_to_right = 0;
                  curr->total_weight =  10 + curr->left + curr->right + curr->add_to_left;
                }
              }
           }
           else if(curr->use_other_balance_right>=num_of_balances_2)//jika mau balance yg ga ada
           {                                                //hitung seperti tidak ada tambahan balance                       
              balance_diff = curr->right - curr->left;
              if(balance_diff == 0)
              {
                curr->total_weight = 10 + curr->left + curr->right;
                curr->add_to_left = 0;
                curr->add_to_right = 0;
              }
              else
              {
                if(balance_diff<0)//jika KIRI lebih berat
                {
                  curr->add_to_right = balance_diff*-1;
                  curr->add_to_left = 0;
                  curr->total_weight =  10 + curr->left + curr->right + curr->add_to_right;
                }
                else if(balance_diff>0)//jika KANAN lebih berat
                {
                  curr->add_to_left = balance_diff;
                  curr->add_to_right = 0;
                  curr->total_weight =  10 + curr->left + curr->right + curr->add_to_left;
                }
              } 
           }
        }
        //jika KANAN dan KIRI pake other balance
        else
        {
            //jika kedua neracanya ketemu
            if(curr->use_other_balance_left<num_of_balances_2 && curr->use_other_balance_right<num_of_balances_2)
            {
               int counter_left_use_other = 0;
               int counter_right_use_other = 0;   
               curr2=root;//loop dari root
               if(curr2!=0)
               {
                    while(curr2->next != 0)
                    {
                        counter_left_use_other++;
                        if(counter_left_use_other-1 == curr->use_other_balance_left)break;
                        curr2=curr2->next;
                    }
               }
               curr->left = curr->left+curr2->total_weight; 
               
               curr2=root;//loop dari root lagi
               if(curr2!=0)
               {
                  while(curr2->next != 0)
                  {
                    counter_right_use_other++;
                    if(counter_right_use_other-1 == curr->use_other_balance_right)break;
                    curr2=curr2->next;
                  }
               }
               curr->right = curr->right+curr2->total_weight;  
               balance_diff = curr->right - curr->left;
               if(balance_diff == 0)
               {
                 curr->total_weight = 10 + curr->left + curr->right;
                 curr->add_to_left = 0;
                 curr->add_to_right = 0;
               }
               else
               {
                 if(balance_diff<0)//jika KIRI lebih berat
                 {
                   curr->add_to_right = balance_diff*-1;
                   curr->add_to_left = 0;
                   curr->total_weight =  10 + curr->left + curr->right + curr->add_to_right;
                 }
                 else if(balance_diff>0)//jika KANAN lebih berat
                 {
                   curr->add_to_left = balance_diff;
                   curr->add_to_right = 0;
                   curr->total_weight =  10 + curr->left + curr->right + curr->add_to_left;
                 }
               }      
            }
            //jika yang KIRI ketemu, yang KANAN ga ketemu
            else if(curr->use_other_balance_left<num_of_balances_2 && curr->use_other_balance_right>=num_of_balances_2)
            {
               int counter_left_use_other = 0;
               if(curr->use_other_balance_left<num_of_balances_2)
               {
                  curr2=root;
                  if(curr2!=0)
                  {
                     while(curr2->next != 0)
                     {
                        counter_left_use_other++;
                        if(counter_left_use_other-1 == curr->use_other_balance_left)break;
                        curr2=curr2->next;
                     }
                  }
                  curr->left = curr->left+curr2->total_weight;
              
                  balance_diff = curr->right - curr->left;
                  if(balance_diff == 0)
                  {
                    curr->total_weight = 10 + curr->left + curr->right;
                    curr->add_to_left = 0;
                    curr->add_to_right = 0;
                  }
                  else
                  {
                    if(balance_diff<0)//jika KIRI lebih berat
                    {
                      curr->add_to_right = balance_diff*-1;
                      curr->add_to_left = 0;
                      curr->total_weight =  10 + curr->left + curr->right + curr->add_to_right;
                    }
                    else if(balance_diff>0)//jika KANAN lebih berat
                    {
                      curr->add_to_left = balance_diff;
                      curr->add_to_right = 0;
                      curr->total_weight =  10 + curr->left + curr->right + curr->add_to_left;
                    }
                  }
               }
            }
            //jika yang KANAN ketemu, yang KIRI ga ketemu
            else if(curr->use_other_balance_left>=num_of_balances_2 && curr->use_other_balance_right<num_of_balances_2)
            {
                 int counter_right_use_other = 0;//hitung mundur. Karena balance 0 ada di paling akhir
                 if(curr->use_other_balance_right<num_of_balances_2)
                 {
                   curr2=root;
                   if(curr2!=0)
                   {
                      while(curr2->next != 0)
                      {
                        counter_right_use_other++;
                        if(counter_right_use_other-1 == curr->use_other_balance_right)break;
                        curr2=curr2->next;
                      }
                   }
                   curr->right = curr->right+curr2->total_weight;
              
                   balance_diff = curr->right - curr->left;
                   if(balance_diff == 0)
                   {
                     curr->total_weight = 10 + curr->left + curr->right;
                     curr->add_to_left = 0;
                     curr->add_to_right = 0;
                   }
                   else
                   {
                     if(balance_diff<0)//jika KIRI lebih berat
                     {
                       curr->add_to_right = balance_diff*-1;
                       curr->add_to_left = 0;
                       curr->total_weight =  10 + curr->left + curr->right + curr->add_to_right;
                     }
                     else if(balance_diff>0)//jika KANAN lebih berat
                     {
                       curr->add_to_left = balance_diff;
                       curr->add_to_right = 0;
                       curr->total_weight =  10 + curr->left + curr->right + curr->add_to_left;
                     }
                   }
                 }
              }//end of KANAN ketemu, yang KIRI ga ketemu
           }
      }//end of IF CURR != 0
   }//end of FOR
   
    curr = root;
    if ( curr != 0 ) 
    { 
      while ( curr->next != 0 ) 
      {
          cout<<"LEFT: "<<curr->add_to_left<<" RIGHT:"<<curr->add_to_right<<endl;
          curr = curr->next;
      }
          cout<<"LEFT: "<<curr->add_to_left<<" RIGHT:"<<curr->add_to_right<<endl;
    }
   
   system("PAUSE");
   return 0;
}
