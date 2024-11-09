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

void Database_close(struct Connection *conn);

void die(const char *message,struct Connection *conn)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    Database_close(conn);  
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to load database.",conn);
        // printf("%d\n",conn->db->MAX_ROWS);
	conn->db->rows = (struct Address*)malloc(sizeof(struct Address)*conn->db->MAX_ROWS);
	for(size_t i = 0 ; i < conn->db->MAX_ROWS;i++){
		rc = fread(&(conn->db->rows[i].id), sizeof(int), 1, conn->file);
	//	printf("%d\n",conn->db->rows[i].id);
		if(rc != 1) die("Failed to load id.",conn);
		rc = fread(&(conn->db->rows[i].set), sizeof(int), 1, conn->file);
	//	printf("%d\n",conn->db->rows[i].set);
		if(rc != 1) die("Failed to load set.",conn);
		conn->db->rows[i].name = (char*)malloc(conn->db->MAX_DATA);
		conn->db->rows[i].email = (char*)malloc(conn->db->MAX_DATA);
		rc = fread(conn->db->rows[i].name, conn->db->MAX_DATA, 1, conn->file);
		if(rc != 1) die("Failed to load name.",conn);
		rc = fread(conn->db->rows[i].email, conn->db->MAX_DATA, 1, conn->file);
		if(rc != 1) die("Failed to load set.",conn);
	}
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error",conn);

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error",conn);

    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    if(!conn->file) die("Failed to open the file",conn);

    return conn;
}

void Database_close(struct Connection *conn)
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

void Database_write(struct Connection *conn)
{
    rewind(conn->file);//  reset the conn->file to the begining of the file . 

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to write database.",conn);
     
    for (size_t i = 0; i < conn->db->MAX_ROWS; i++) {
         if(fwrite(&((conn->db->rows[i]).id), sizeof(int), 1, conn->file) != 1)
              die("Failed to write id.",conn);
         if(fwrite(&((conn->db->rows[i]).set), sizeof(int), 1, conn->file) != 1)
              die("Failed to write set.",conn);
         if(fwrite((conn->db->rows[i]).name, conn->db->MAX_DATA, 1, conn->file) != 1)
              die("Failed to write name.",conn);
         if(fwrite((conn->db->rows[i]).email, conn->db->MAX_DATA, 1, conn->file) != 1)
              die("Failed to write email.",conn);
     }
    rc = fflush(conn->file);// tell the computer that wirte the data to the disk immedately.
    if(rc == -1) die("Cannot flush database.",conn);
}

void Database_create(struct Connection *conn,int MAX_ROWS,int MAX_DATA)
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

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];

    //printf("%s,%s\n",name,email);
    if(addr->set) die("Already set, delete it first",conn);
   // addr->name = (char*)malloc(conn->db->MAX_DATA);
   // addr->email = (char*)malloc(conn->db->MAX_DATA);
    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name,conn->db->MAX_DATA);
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed",conn);
    //printf("%s,%s\n",conn->db->rows[id].name,addr->name);
    res = strncpy(addr->email, email,conn->db->MAX_DATA);
    if(!res) die("Email copy failed",conn);
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set",conn);
    }
}

void Database_delete(struct Connection *conn, int id)
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

void Database_list(struct Connection *conn)
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

void Database_find(struct Connection *conn, char *name)
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
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]",conn);
    if(argc > 3) id = atoi(argv[3]);
//    if(id >= MAX_ROWS) die("There's not that many records.");

    switch(action) {
        case 'c':
            if(argc != 5) die("Need MAX_ROWS,MAX_DATA",conn);
            MAX_ROWS = atoi(argv[argc-2]);
            MAX_DATA = atoi(argv[argc-1]);
            //printf("%d %d",MAX_ROWS,MAX_DATA);
            Database_create(conn,MAX_ROWS,MAX_DATA);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get",conn);

            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set",conn);
//            printf("%d", conn->db->rows[2].id);
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete",conn);

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

 	case 'f':
	    Database_find(conn,argv[argc-1]);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list",conn);
    }

    Database_close(conn);

    return 0;
}
