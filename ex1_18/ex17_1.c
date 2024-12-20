#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int MAX_DATA,MAX_ROWS;
struct Address {
    int id;
    int set;
    char* name;
    char* email;
};

struct Database {
    struct Address* rows;
    int MAX_DATA;
    int MAX_ROWS;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

struct Connection *conn = NULL;



void Database_close();

void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    Database_close();  
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load()
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to load database.");
        // printf("%d\n",conn->db->MAX_ROWS);
	conn->db->rows = (struct Address*)malloc(sizeof(struct Address)*conn->db->MAX_ROWS);
	for(size_t i = 0 ; i < conn->db->MAX_ROWS;i++){
		rc = fread(&(conn->db->rows[i].id), sizeof(int), 1, conn->file);
	//	printf("%d\n",conn->db->rows[i].id);
		if(rc != 1) die("Failed to load id.");
		rc = fread(&(conn->db->rows[i].set), sizeof(int), 1, conn->file);
	//	printf("%d\n",conn->db->rows[i].set);
		if(rc != 1) die("Failed to load set.");
		conn->db->rows[i].name = (char*)malloc(conn->db->MAX_DATA);
		conn->db->rows[i].email = (char*)malloc(conn->db->MAX_DATA);
		rc = fread(conn->db->rows[i].name, conn->db->MAX_DATA, 1, conn->file);
		if(rc != 1) die("Failed to load name.");
		rc = fread(conn->db->rows[i].email, conn->db->MAX_DATA, 1, conn->file);
		if(rc != 1) die("Failed to load set.");
	}
}

struct Connection *Database_open(const char *filename, char mode)
{
    conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error");

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error");

    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load();
        }
    }

    if(!conn->file) die("Failed to open the file");

    return conn;
}

void Database_close()
{
    if(conn) {
        for(int i = 0; i < conn->db->MAX_ROWS ; i++){
	
	if(conn->db->rows[i].name) free(conn->db->rows[i].name);

	if(conn->db->rows[i].email) free(conn->db->rows[i].email);
	}
	if(conn->db->rows) free(conn->db->rows);

        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
}

void Database_write()
{
    rewind(conn->file);//  reset the conn->file to the begining of the file . 

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to write database.");
     
    for (size_t i = 0; i < conn->db->MAX_ROWS; i++) {
         if(fwrite(&((conn->db->rows[i]).id), sizeof(int), 1, conn->file) != 1)
              die("Failed to write id.");
         if(fwrite(&((conn->db->rows[i]).set), sizeof(int), 1, conn->file) != 1)
              die("Failed to write set.");
         if(fwrite((conn->db->rows[i]).name, conn->db->MAX_DATA, 1, conn->file) != 1)
              die("Failed to write name.");
         if(fwrite((conn->db->rows[i]).email, conn->db->MAX_DATA, 1, conn->file) != 1)
              die("Failed to write email.");
     }
    rc = fflush(conn->file);// tell the computer that wirte the data to the disk immedately.
    if(rc == -1) die("Cannot flush database.");
}

void Database_create(int MAX_ROWS,int MAX_DATA)
{
    int i = 0;
    conn->db->MAX_ROWS = MAX_ROWS;
    conn->db->MAX_DATA = MAX_DATA;
    conn->db->rows = (struct Address*)malloc(MAX_ROWS*sizeof(struct Address));

    for(i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0};
	addr.name = (char*)malloc(MAX_DATA*sizeof(char));
	addr.email = (char*)malloc(MAX_DATA*sizeof(char));
        //printf("id:%d set:%d\n",addr.id,addr.set);
	memset(addr.name, 0, conn->db->MAX_DATA); //memeset : initailize the memory you alloc , it must be done to avoid SG11.
	memset(addr.email, 0, conn->db->MAX_DATA);

        //printf("id:%s set:%s\n",addr.name,addr.email);

        // then just assign it
        conn->db->rows[i] = addr;
        
        //printf("id:%d set:%d\n",conn->db->rows[i].id,conn->db->rows[i].set);
    }
}

void Database_set(int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];

    //printf("%s,%s\n",name,email);
    if(addr->set) die("Already set, delete it first");
   // addr->name = (char*)malloc(conn->db->MAX_DATA);
   // addr->email = (char*)malloc(conn->db->MAX_DATA);
    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name,conn->db->MAX_DATA);
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed");
    //printf("%s,%s\n",conn->db->rows[id].name,addr->name);
    res = strncpy(addr->email, email,conn->db->MAX_DATA);
    if(!res) die("Email copy failed");
}

void Database_get(int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(int id)
{
    struct Address addr = {.id = id, .set = 0};
    free(conn->db->rows[id].name);
    free(conn->db->rows[id].email);
    conn->db->rows[id] = addr;
    conn->db->rows[id].name = (char*)malloc(conn->db->MAX_DATA);//you have to malloc the memory & initialize it .
    conn->db->rows[id].email = (char*)malloc(conn->db->MAX_DATA);
    memset(conn->db->rows[id].name, 0, conn->db->MAX_DATA);
    memset(conn->db->rows[id].email, 0, conn->db->MAX_DATA);
 
  

}

void Database_list()
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < db->MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

void Database_find(char *name)
{
	int m = 0 ;
	for(int i = 0; i < conn->db->MAX_ROWS;i++){
	struct Address *addr = &conn->db->rows[i];
	//printf("%s  %s \n", addr->name , name);
	if(strcmp(name,addr->name)==0) {
		Address_print(addr);
		m++;
	//	printf("%d\n",m);
	}
	} 
	if (m==0) printf("I can't find %s\n",name);

}
int main(int argc, char *argv[])
{

    char *filename = argv[1];
    char action = argv[2][0];
    Database_open(filename, action);
    int id = 0;

    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");
    if(argc > 3) id = atoi(argv[3]);
//    if(id >= MAX_ROWS) die("There's not that many records.");

    switch(action) {
        case 'c':
            if(argc != 5) die("Need MAX_ROWS,MAX_DATA");
            MAX_ROWS = atoi(argv[argc-2]);
            MAX_DATA = atoi(argv[argc-1]);
            //printf("%d %d",MAX_ROWS,MAX_DATA);
            Database_create(MAX_ROWS,MAX_DATA);
            Database_write();
            break;

        case 'g':
            if(argc != 4) die("Need an id to get");

            Database_get(id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set");
//            printf("%d", conn->db->rows[2].id);
            Database_set(id, argv[4], argv[5]);
            Database_write();
            break;

        case 'd':
            if(argc != 4) die("Need id to delete");

            Database_delete(id);
            Database_write();
            break;

        case 'l':
            Database_list();
            break;

 	case 'f':
	    Database_find(argv[argc-1]);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close();

    return 0;
}
