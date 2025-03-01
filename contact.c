#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"contact.h"
//#include"populate.h"

/*create:23
search:132
list:222
edit:233
delate:708
save:992
load:934
 */


void initilize(Addressbook *addressbook)
{
	addressbook->contact_count=0;
	FILE *fptr;
	fptr=fopen("contact.csv","r");
	fscanf(fptr,"#%d\n",&addressbook->contact_count);
	for(int i=0;i<addressbook->contact_count;i++)
	{
		fscanf(fptr," %[^,],%[^,],%[^\n]\n",addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
	}
	fclose(fptr);
}

void create_contact(Addressbook *addressbook)
{
	char name[50],mobile[15],mailid[30];
	//reading name
	printf("Enter name:");
	scanf(" %[^\n]",name);
	strcpy(addressbook->contacts[addressbook->contact_count].name,name);

	//reading mobileno
label1:	printf("Enter mobile number:");
	scanf(" %[^\n]",mobile);
	int mobilelen=0;
	for(int i=0;mobile[i];i++)
	{
		mobilelen++;
	}
	//checking mobilenumber is 10 digits or not
	if(mobilelen==10)
	{
		//checking mobile number characters are between 0 to 9 or not
		int i=0;
		while(mobile[i])
		{
			if(mobile[i]>='0' && mobile[i]<='9')
			{
				i++;
			}
			else
			{
				break;
			}
		}		
		if(mobile[i]!='\0')
		{
			printf("\n");
label2:			printf("Invalid number\n");
label3:			printf("Enter your choice\n"); 
			printf("1.Re-ener mobile number\n");
			printf("2.Exit\n");
			int ch;
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					goto label1;
					break;
				case 2:
					return;
				default:
					printf("Enter valid option!\n");
					goto label3;
			}
		}
		else
		{
			//checking mobile number is exist or not
			int j;
			for(j=0;j<addressbook->contact_count;j++)
			{
				if(strstr(addressbook->contacts[j].mobile,mobile)!=NULL)
				{
					printf("\nAlready Exist!\n");
					goto label3;
					break;
				}
			}
			if(j==addressbook->contact_count)
			{
				strcpy(addressbook->contacts[addressbook->contact_count].mobile,mobile);
label4:				printf("Enter Mailid:");
				scanf(" %[^\n]",mailid);
				//checking mailid is valid or not
				if((strstr(mailid,"@")!=NULL) && (strstr(mailid,".com")!=NULL))
				{
					printf("\nContact Created Successfully!\n");
					strcpy(addressbook->contacts[addressbook->contact_count].mailid,mailid);
					addressbook->contact_count++;
				}
				else
				{
					printf("\n");
					printf("Invalid Mailid\n");
label5:                                 printf("Enter your choice:\n");
					printf("1.Re-Enter mailid\n");
					printf("2.Exit\n");
					int ch;
					scanf("%d",&ch);
					switch(ch)
					{
						case 1:
							goto label4;
							break;
						case 2:
							return;
						default:
							printf("Enter valid option!\n");
							goto label5;
					}
				}
			}
		}
	}
	else
	{
		goto label2;
	}
}


void search_contact(Addressbook *addressbook)
{
label1:	printf("Choose which data will you give\n");
	printf("1.By Name\n");
	printf("2.By Mobileno\n");
	printf("3.By MailID\n");
	int ch,fact=0;
	printf("Enter your choice:");
	scanf("%d",&ch);
	char search[30];
	printf("\n");
	switch(ch)
	{
		case 1:
			printf("Enter Search Name:");
			scanf(" %[^\n]",search);
			printf("\n");
			for(int i=0;i<addressbook->contact_count;i++)
			{
				if(strstr(addressbook->contacts[i].name,search)!=NULL)
				{
					printf("%-18s%-15s%-20s\n",addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
					fact=1;
				}
			}
			if(fact==0)
			{
				printf("Given Name is not found\n");
				printf("\n");
				return;
			}
			break;
		case 2:
			printf("Enter Search Mobileno:");
			scanf(" %[^\n]",search);
			printf("\n");
			for(int i=0;i<addressbook->contact_count;i++)
			{
				if(strstr(addressbook->contacts[i].mobile,search)!=NULL)                                  
				{	printf("%-18s%-15s%-20s\n",addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
					fact=1;
				}
			}
			if(fact==0)
			{
				printf("Given Mobileno is not found\n");
				printf("\n");
				return;
			}
			break;
		case 3:
			printf("Enter Search Mailid:");
			scanf(" %[^\n]",search);
			printf("\n");
			for(int i=0;i<addressbook->contact_count;i++)
			{
				if(strstr(addressbook->contacts[i].mailid,search)!=NULL)
				{
					printf("%-18s%-15s%-20s\n",addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
					fact=1;
				}
			}
			if(fact==0)
			{
				printf("Given Mailid is not found\n");
				printf("\n");
				return;
			}
			break;
		default:
label2:			printf("Invalid Choice!\n");
			printf("1.Re-enter choice\n");
			printf("2.Exit\n");
			int ch;
			printf("Enter your choice:");
			scanf("%d\n",&ch);
			switch(ch)
			{
				case 1:
					goto label1;
					break;
				case 2:
					return;
				default:
					goto label2;
			}
	}
}


void list_contact(Addressbook *addressbook)
{
	printf("---------------------------------------------------------------\n");
	printf("%-18s%-15s%-20s\n","Name","Mobileno","MailID");
	printf("---------------------------------------------------------------\n");	
	for(int i=0;i<addressbook->contact_count;i++)
	{
		printf("%-18s%-15s%-20s\n",addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
	}
}

void edit_contact(Addressbook *addressbook)
{
	int ch,fact=0,index,ch1;
	char edit[30],new[30];
label1:	printf("\nChoose which data you will give:\n");
	printf("1.By name\n");
	printf("2.By mobileno\n");
	printf("3.By mailid\n");
	printf("Enter your choice:");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
label9:			printf("\nEnter name:");
			scanf(" %[^\n]",edit);
			for(int i=0;i<addressbook->contact_count;i++)
			{
				if(strstr(addressbook->contacts[i].name,edit)!=NULL)
				{
					printf("[%d] %-18s%-15s%-20s\n",i+1,addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
					fact=1;
				}
			}
			if(fact==0)
			{

				printf("Given name is not found!\n");
				return;
			}
			printf("Enter which index data you want to edit:");
			scanf("%d",&index);
label2:			printf("\nChoose which data do you want to edit\n");
			printf("1.Edit Name\n");
			printf("2.Edit Mobile\n");
			printf("3.Edit Mailid\n");
			printf("Enter your choice:");
			scanf("%d",&ch1);
			switch(ch1)
			{
				case 1:
					printf("\nEnter new name:");
					scanf(" %[^\n]",new);
					strcpy(addressbook->contacts[index-1].name,new);
					printf("\nEdit succesfully!\n");
					break;
				case 2:
label11:						printf("\nEnter new mobileno:");
							scanf(" %[^\n]",new);
							int mobilelen=0;
							for(int i=0;new[i]!='\0';i++)
							{
								mobilelen++;
							}
							if(mobilelen==10)
							{
								int i=0;
								while(new[i])
								{
									if(new[i]>='0' && new[i]<='9')
									{
										i++;
									}
									else
									{
										break;
									}
								}
								if(new[i]!='\0')
								{
									printf("Invalid number\n");
label12:									printf("Enter your choice:\n");
										printf("1.Re-enter number\n");
										printf("2.Exit\n");
										int ch;
										scanf("%d",&ch);
										switch(ch)
										{
											case 1:
												goto label11;
												return;
											case 2:
												return;
											default:
												printf("Enter valid choice!\n");
												goto label12;
										}
								}
								else
								{
									int j;
									for(j=0;j<addressbook->contact_count;j++)
									{
										if(strstr(addressbook->contacts[j].mobile,new)!=NULL)
										{
											printf("Already Exist!\n");
											goto label12;
											break;
										}
									}
									if(j==addressbook->contact_count)
									{
										strcpy(addressbook->contacts[index-1].mobile,new);
										printf("\nPhone Number Edit succesfully!\n");
									}
								}
							}
							else
							{
								printf("Invalid number!\n");
								goto label11;
							}
							break;
				case 3:
label13:						printf("\nEnter new mailid:");
							scanf(" %[^\n]",new);
							if((strstr(new,"@")!=NULL) && (strstr(new,".com")!=NULL))
							{
								strcpy(addressbook->contacts[index].mailid,new);
								printf("Mailid edited Successfully!\n");
							}
							else
							{
								printf("Invalid Mailid!\n");
label14:							printf("1.Re enter mailid\n");
								printf("2.Exit\n");
								printf("Enter your choice:");
								int ch;
								scanf("%d",&ch);
								switch(ch)
								{
									case 1:
										goto label13;
										break;
									case 2:
										return;
									default:
										printf("Entervalid choice!\n");
										goto label14;
										break;
								}
							}
							break;
				default:
label3:							printf("\nInvalid choice!\n");
							printf("1.Re-enter choice\n");
							printf("2.Exit\n");
							printf("Enter your choice:");
							int ch;
							scanf("%d",&ch);
							switch(ch)
							{
								case 1:
									goto label2;
									break;
								case 2:
									return;
								default:
									goto label3;
							}
			}
			break;
		case 2:
label15:		printf("\nEnter Mobileno:");
			scanf(" %[^\n]",edit);
			for(int i=0;i<addressbook->contact_count;i++)
			{
				if(strstr(addressbook->contacts[i].mobile,edit)!=NULL)
				{
					printf("[%d] %-18s%-15s%-20s\n",i+1,addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);	
					fact=1;
				}
			}
			if(fact==0)
			{
				printf("Given Number is not found!\n");
				return;
			}
			printf("Enter which index data you want to edit:");
			scanf("%d",&index);
label17:                 printf("\nChoose which data do you want to edit\n");
			 printf("1.Edit Name\n");
			 printf("2.Edit Mobile\n");
			 printf("3.Edit Mailid\n");
			 printf("Enter your choice:");
			 scanf("%d",&ch1);
			 switch(ch1)
			 {
				 case 1:
					 printf("\nEnter new name:");
					 scanf(" %[^\n]",new);
					 strcpy(addressbook->contacts[index-1].name,new);
					 printf("\nEdit succesfully!\n");
					 break;
				 case 2:
label18:                                                printf("\nEnter new mobileno:");
							scanf(" %[^\n]",new);
							int mobilelen=0;
							for(int i=0;new[i]!='\0';i++)
							{
								mobilelen++;
							}
							if(mobilelen==10)
							{
								int i=0;
								while(new[i])
								{
									if(new[i]>='0' && new[i]<='9')
									{
										i++;
									}
									else
									{
										break;
									}
								}
								if(new[i]!='\0')
								{
									printf("Invalid number\n");
label19:                                                                        printf("Enter your choice:\n");
										printf("1.Re-enter number\n");
										printf("2.Exit\n");
										int ch;
										scanf("%d",&ch);
										switch(ch)
										{
											case 1:
												goto label18;
												return;
											case 2:
												return;
											default:
												printf("Enter valid choice!\n");
												goto label19;
										}
								}
								else
								{
									int j;
									for(j=0;j<addressbook->contact_count;j++)
									{
										if(strstr(addressbook->contacts[j].mobile,new)!=NULL)
										{
											printf("Already Exist!\n");
											goto label18;
											break;
										}
									}
									if(j==addressbook->contact_count)
									{
										strcpy(addressbook->contacts[index-1].mobile,new);
										printf("\nPhone Number Edit succesfully!\n");
									}
								}
							}
							else
							{
								printf("Invalid Number!\n");
								goto label18;
							}
							break;
				 case 3:
label20:                                                printf("\nEnter new mailid:");
							scanf(" %[^\n]",new);
							if((strstr(new,"@")!=NULL) && (strstr(new,".com")!=NULL))
							{
								strcpy(addressbook->contacts[index-1].mailid,new);
								printf("Mailid edited Successfully!\n");
							}
							else
							{
label21:                                                        printf("1.Re enter mailid\n");
								printf("2.Exit\n");
								printf("Enter your choice:");
								int ch;
								scanf("%d",&ch);
								switch(ch)
								{
									case 1:
										goto label20;
										break;
									case 2:
										return;
									default:
										printf("Entervalid choice!\n");
										goto label21;
										break;
								}
							}
							break;
				 default:
label22:                                                 printf("\nInvalid choice!\n");
							 printf("1.Re-enter choice\n");
							 printf("2.Exit\n");
							 printf("Enter your choice:");
							 int ch;
							 scanf("%d",&ch);
							 switch(ch)
							 {
								 case 1:
									 goto label17;
									 break;
								 case 2:
									 return;
								 default:
									 goto label22;
							 }
			 }
			 break;
		case 3:
label23:		printf("\nEnter Mailid:");
			scanf(" %[^\n]",edit);
			for(int i=0;i<addressbook->contact_count;i++)
			{
				if(strstr(addressbook->contacts[i].mailid,edit)!=NULL)
				{
					printf("[%d] %-18s%-15s%-20s\n",i+1,addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
					fact=1;
				}
			}
			if(fact==0)
			{
				printf("Given NMailid is not found!\n");
				return;
			}
			printf("Enter which index data you want to edit:");
			scanf("%d",&index);
label25:                 printf("\nChoose which data do you want to edit\n");
			 printf("1.Edit Name\n");
			 printf("2.Edit Mobile\n");
			 printf("3.Edit Mailid\n");
			 printf("Enter your choice:");
			 scanf("%d",&ch1);
			 switch(ch1)
			 {
				 case 1:
					 printf("\nEnter new name:");
					 scanf(" %[^\n]",new);
					 strcpy(addressbook->contacts[index-1].name,new);
					 printf("\nEdit succesfully!\n");
					 break;
				 case 2:
label26:                                                printf("\nEnter new mobileno:");
							scanf(" %[^\n]",new);
							int mobilelen=0;
							for(int i=0;new[i]!='\0';i++)
							{
								mobilelen++;
							}
							if(mobilelen==10)
							{
								int i=0;
								while(new[i])
								{
									if(new[i]>='0' && new[i]<='9')
									{
										i++;
									}
									else
									{
										break;
									}
								}
								if(new[i]!='\0')
								{
									printf("Invalid number\n");
label27:                                                                        printf("Enter your choice:\n");
										printf("1.Re-enter number\n");
										printf("2.Exit\n");
										int ch;
										scanf("%d",&ch);
										switch(ch)
										{
											case 1:
												goto label26;
												return;
											case 2:
												return;
											default:
												printf("Enter valid choice!\n");
												goto label27;
										}
								}
								else
								{
									int j;
									for(j=0;j<addressbook->contact_count;j++)
									{
										if(strstr(addressbook->contacts[j].mobile,new)!=NULL)
										{
											printf("Already Exist!\n");
											goto label27;
											break;
										}
									}
									if(j==addressbook->contact_count)
									{
										strcpy(addressbook->contacts[index-1].mobile,new);
										printf("\nPhone Number Edit succesfully!\n");
									}
								}
							}
							else
							{
								printf("Invalid number!\n");
								goto label26;
							}
							break;
				 case 3:
label28:                                                printf("\nEnter new mailid:");
							scanf(" %[^\n]",new);
							if((strstr(new,"@")!=NULL) && (strstr(new,".com")!=NULL))
							{
								strcpy(addressbook->contacts[index].mailid,new);
								printf("Mailid edited Successfully!\n");
							}
							else
							{
label29:                                                        printf("1.Re enter mailid\n");
								printf("2.Exit\n");
								printf("Enter your choice:");
								int ch;
								scanf("%d",&ch);
								switch(ch)
								{
									case 1:
										goto label28;
										break;
									case 2:
										return;
									default:
										printf("Entervalid choice!\n");
										goto label29;
										break;
								}
							}
							break;
				 default:
label30:                                                 printf("\nInvalid choice!\n");
							 printf("1.Re-enter choice\n");
							 printf("2.Exit\n");
							 printf("Enter your choice:");
							 int ch;
							 scanf("%d",&ch);
							 switch(ch)
							 {
								 case 1:
									 goto label25;
									 break;
								 case 2:
									 return;
								 default:
									 goto label30;
							 }
			 }
			 break;
		default:
label31:					 printf("Invalid choice!\n");
						 printf("1.Re enter choice\n");
						 printf("2.Exit\n");
						 printf("Enter your choice:");
						 scanf("%d",&ch1);
						 switch(ch)
						 {
							 case 1:
								 goto label1;
								 break;
							 case 2:
								 return;
							 default:
								 goto label31;
								 break;
						 }
	}
}

void delete_contact(Addressbook *addressbook)
{
label1:	printf("Choose which data to give\n");
	printf("1.Name\n");
	printf("2.Mobileno\n");
	printf("3.Mailid\n");
	int ch,fact=0,n,j;
	char search[30];
	printf("Enter your choice:");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			printf("Enter Search Name:");
			scanf(" %[^\n]",search);
			printf("\n");
			for(int i=0;i<addressbook->contact_count;i++)
			{
				if(strstr(addressbook->contacts[i].name,search)!=NULL)
				{
					printf("[%d] %-18s%-15s%-20s\n",i+1,addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
					fact=1;
				}
			}
			if(fact==0)
			{
				printf("Given Name is not found\n");
				printf("\n");
				return;
			}
label2:			printf("\nEnter which index data you want to delete:");
			scanf("%d",&n);
			if(n<=addressbook->contact_count)
			{
				if(strstr(addressbook->contacts[n-1].name,search)!=NULL)
				{
					for(j=n-1;j<addressbook->contact_count;j++)
					{
						addressbook->contacts[j]=addressbook->contacts[j+1];
					}
					if(j==addressbook->contact_count)
					{
						printf("\n%d index contact Deleted succesfully!\n",n);
						addressbook->contact_count--;
					}
				}
				else
				{
					printf("\nInvalid index value!\n");
					int ch;
label3:				        printf("1.Re-enter index\n");
					printf("2.Exit\n");
					printf("Enter your choice:");
					scanf("%d",&ch);
					switch(ch)
					{
						case 1:
							goto label2;
							break;
						case 2:
							return;
						default:
							printf("Invalid choice!\n");
							goto label3;
					}
				}
			}
			else
			{
				printf("Invalid Index!\n");
			}
			break;
		case 2:
			printf("Enter Search Mobileno:");
			scanf(" %[^\n]",search);
			printf("\n");
			for(int i=0;i<addressbook->contact_count;i++)
			{
				if(strstr(addressbook->contacts[i].mobile,search)!=NULL)
				{
					printf("[%d] %-18s%-15s%-20s\n",i+1,addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
					fact=1;
				}
			}
			if(fact==0)
			{
				printf("Given Mobileno is not found\n");
				printf("\n");
				return;
			}
label4:			printf("\nEnter which index data you want to delete:");
			scanf("%d",&n);
			if(n<=addressbook->contact_count)
			{
				if(strstr(addressbook->contacts[n-1].mobile,search)!=NULL)
				{
					for(j=n-1;j<addressbook->contact_count;j++)
					{
						addressbook->contacts[j]=addressbook->contacts[j+1];
					}
					if(j==addressbook->contact_count)
					{
						printf("\n%d index contact Deleted succesfully!\n",n);
						addressbook->contact_count--;
					}
				}
				else
				{
					printf("\nInvalid index value!\n");
					int ch;
label5:                                 printf("1.Re-enter index\n");
					printf("2.Exit\n");
					printf("Enter your choice:");
					scanf("%d",&ch);
					switch(ch)
					{
						case 1:
							goto label4;
							break;
						case 2:
							return;
						default:
							printf("Invalid choice!\n");
							goto label5;
					}
				}
			}
			else
			{
				printf("Invalid Index!\n");
				goto label4;
			}
			break;
		case 3:
			printf("Enter Search Mailid:");
			scanf(" %[^\n]",search);
			printf("\n");
			for(int i=0;i<addressbook->contact_count;i++)
			{
				if(strstr(addressbook->contacts[i].mailid,search)!=NULL)
				{
					printf("[%d] %-18s%-15s%-20s\n",i+1,addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
					fact=1;
				}
			}
			if(fact==0)
			{
				printf("Given Mailid is not found\n");
				printf("\n");
				return;
			}
label6:			printf("\nEnter which index data you want to delete:");
			scanf("%d",&n);
			if(n<=addressbook->contact_count)
			{
				if(strstr(addressbook->contacts[n-1].mailid,search)!=NULL)
				{
					for(j=n-1;j<addressbook->contact_count;j++)
					{
						addressbook->contacts[j]=addressbook->contacts[j+1];
					}
					if(j==addressbook->contact_count)
					{
						printf("\n%d index contact Deleted succesfully!\n",n);
						addressbook->contact_count--;
					}
				}
				else
				{
					printf("\nInvalid index value!\n");
					int ch;
label7:                                 printf("1.Re-enter index\n");
					printf("2.Exit\n");
					printf("Enter your choice:");
					scanf("%d",&ch);
					switch(ch)
					{
						case 1:
							goto label6;
							break;
						case 2:
							return;
						default:
							printf("Invalid choice!\n");
							goto label7;
					}
				}
			}
			else
			{
				printf("Invalid Index!\n");
				goto label6;
			}
			break;
		default:
label8:			printf("Invalid choice!\n");
			printf("1.Re-enter\n");
			printf("2.Exit\n");
			int ch;
			printf("Enter your choice:");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					goto label1;
					break;
				case 2:
					return;
				default:
					goto label8;
			}
	}
}

void save_contact(Addressbook *addressbook)
{
	FILE *fptr;
	fptr=fopen("contact.csv","w");
	fprintf(fptr, "#%d\n",addressbook->contact_count);
	for(int i=0;i<addressbook->contact_count;i++)
	{
		fprintf(fptr, "%s,%s,%s\n",addressbook->contacts[i].name,addressbook->contacts[i].mobile,addressbook->contacts[i].mailid);
	}
	fclose(fptr);
}

