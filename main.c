#include<stdio.h>
#include"contact.h"
int main()
{
	int choice;
	Addressbook addressbook;
	initilize(&addressbook);
	while(1)
	{
		printf("Address Book menu:\n");
		printf("1.Create Contact\n");
		printf("2.Search Contact\n");
		printf("3.Edit Contact\n");
		printf("4.Delete Contact\n");
		printf("5.List Contact\n");
		printf("6.Save Contact\n");
		printf("7.Exit\n");
		printf("\nEnter your choice:");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:create_contact(&addressbook);
			       break;
			case 2:search_contact(&addressbook);   
			       break;
			case 3:edit_contact(&addressbook);
			       break;
			case 4:delete_contact(&addressbook);
			       break;
			case 5:list_contact(&addressbook);
			       break;
			case 6:save_contact(&addressbook);
			       printf("Data Saved!\n");
			       break;
			case 7:
label1:			       printf("1.Data save\n");
			       printf("2.Exit,Data already saved\n");
			       printf("Enter your choice:");
			       int ch;
			       scanf("%d",&ch);
			       switch(ch)
			       {
				       case 1:
					       save_contact(&addressbook);
					       printf("\nData Saved!\n");
					       return 0;
					       break;
				       case 2:
					       printf("Exit\n");
					       return 0;
				       default:
					       printf("Enter valid choice!\n");
					       goto label1;
			       }
			       break;
			default:printf("Invalid choice!\nTry again!\n");
		}
		printf("\n");
	}
	return 0;
}	


