#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct
{
	char name[50];
	char mobile[15];
	char mailid[30];
}Contact;

typedef struct
{
	Contact contacts[100];
	int contact_count;
}Addressbook;

void initilize(Addressbook *addressbook);
void create_contact(Addressbook *addressbook);
void list_contact(Addressbook *addressbook);
void edit_contact(Addressbook *addressbook);
void delete_contact(Addressbook *addressbook);
void search_contact(Addressbook *addressbook);
void save_contact(Addressbook *addressbook);                    

#endif
