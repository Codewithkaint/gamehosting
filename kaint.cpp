#include <bits/stdc++.h>
using namespace std;
class Song;
class ListNode{
    public:
        int data;
        ListNode*next;
        ListNode*back;
        ListNode(int val){
            data=val;
            next=back=NULL;
        }

};
unordered_set<int>LikedSong;
unordered_map<int,string>SongList;
unordered_map<string,int>SongName;
unordered_map<int, pair<Song*, int>> RootCollection;
class Song {
public:
    int id; 
    Song* left;
    Song* right;
    Song(){}
  
    Song(int id, string style) {
        RootCollection[id].second=1;
        string str=to_string(id);
        str+="0";
        this->id = stoi(str);
        left = right = NULL;
         
    }

    Song(int cn,int style,string name) {
        int cnt=RootCollection[style].second;
        RootCollection[style].second+=1;
        string str=to_string(style);
        str+=to_string(cnt);
       
       int ids = stoi(str);  
       
     
        enterSong(style,name,ids); 
    }

    Song(int val) {
        id=val;
        left=NULL;
        right=NULL; 
    }
    
    Song(int style,int data) {
   
           LikedSong.insert(data);
        enterLikeSongs(style,data); 
       
    }
    

   
    void enterSong(int style,string name,int ids) {
       
        auto* root = getRoot(style); 

        insertBST(root,ids,name);   
    }
    
    void enterLikeSongs(int style,int data) {
        
        auto* root = getRoot(style); 
   
        insertLikeSongs(root,data);   
    }

    void likeSong(int style,Song* s,string &name) {
        auto* root = getRoot(style); 
        insertBST(root, s->id,name);   
    }

    void fetchSongs(Song *song,ListNode*node) {
       
        traverse(song,node);   
    }

    int deleteSong(int id) {
         string str=to_string(id);
        int styleid=str[0]-'0';
         auto* root =getRoot(styleid);
        int val=-1;
        deleteBST(root,id,val);
           
        if(val==-1) return -1;
        return 1;  
    }
    void deleteLikeSong(int data){
          int val=-1;
          auto root=RootCollection[4].first;
        deleteBST(root,data,val);
    }

    Song* findSong(int data) {
        string str=to_string(data);
        int style=str[0]-'0';
        auto* root =getRoot(style);
        return searchBST(root,data); 
    }

private:
  
    Song* getRoot(int style) {
        
        return RootCollection[style].first;
    }

    
    void insertBST(Song*& root, int id, string name) {
    if (!root) {
        root = new Song(id);
        SongList[id] = name;
        SongName[name]=id;
        return;
    }
    if (id < root->id) {
        insertBST(root->left, id, name);  // Insert in the left subtree
    } else {
        insertBST(root->right, id, name);  // Insert in the right subtree
    }
}
    void insertLikeSongs(Song*& root, int data) {
    if (!root) {
        root = new Song(data);
       
        return;
    }
    if (id < root->id) {
        insertLikeSongs(root->left, data);  // Insert in the left subtree
    } else {
        insertLikeSongs(root->right, data);  // Insert in the right subtree
    }
}


   

   void traverse(Song* song, ListNode* node) {
    if (!song) return;
    
    // Create a new ListNode with the song's ID
    ListNode* newNode = new ListNode(song->id);
   
    // Link the current node to the new node
    node->next = newNode;
    newNode->back = node;

    // Move the node pointer forward
    node = newNode;

    // Recursively traverse left and right subtrees
    traverse(song->left, node);  // Left child
    traverse(song->right, node); // Right child
}


  Song* deleteBST(Song* root, int key,int &val) {
        if (!root){
            val=-1;
            return nullptr;
        }

        if (key < root->id) {
            root->left = deleteBST(root->left, key,val);
        } else if (key > root->id) {
            root->right = deleteBST(root->right, key,val);
        } else {

             
            val=1;
            if (!root->left) {
                Song* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                Song* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children: Find the inorder successor
            Song* minNode = findMin(root->right);
            root->id = minNode->id;
            root->right = deleteBST(root->right, minNode->id,val);
        }
        return root;
    }

    // Placeholder for searching a node in BST
    Song* searchBST(Song* root, int key) {
        if (!root) return NULL;
        if (root->id == key) return root;
        if (key < root->id) return searchBST(root->left, key);
        return searchBST(root->right, key);
    }

    Song* findMin(Song* root) {
        while (root && root->left) {
            root = root->left;
        }
        return root;
    }
};



void addSongs(){
    string name,style;
    int id;
    cout << "\n--- ADD NEW SONG ---" << endl;
cout << "Enter the song name: ";
cin >> name;
cout << "Enter the song style (Bollywood, Hollywood, Tollywood): ";
cin >> style;

  string str;
  
    if(style[0]=='b' || style[0]=='B')
        {id=1;
        str="Bollywood";
        }
    else if(style[0]=='h' || style[0]=='H')
        {id=2;
        str="Hollywood";
        }
    else{
        id=3;
        str="Tollywood";}
        cout << "Adding the song to the " << str << " collection..." << endl;
    Song s(1,id,name);
}

bool starts(string &s){
    if(s.size()>=5 && s[0]=='S' && s[1]=='T' && s[2]=='A' && s[3]=='R' && s[4]=='T')
     return false;
    return true;
   
}

void deleteSongs(){
    int id;
    string name;
 cout << "\n--- DELETE A SONG ---" << endl;
cout << "Enter the name of the song you want to delete: ";
cin >> name;
   id=SongName[name];
    Song s;
    int val=s.deleteSong(id);
    

    if (val == -1)
    cout << "Song not found! Unable to delete." << endl;
else
    cout << "Song '" << name << "' deleted successfully." << endl;

    if(LikedSong.find(id)!=LikedSong.end()){
        s.deleteLikeSong(id);
        LikedSong.erase(id);
    }
    
}

void displaySongs(ListNode* head, bool likes) {
    if (!head) return;
    string str;
    ListNode* start = head;
   cout<<" --- PLAYING SONGS ---"<<endl;
    do {
        cout << "\nPlaying song: " << SongList[head->data] << endl;

       
    str= SongList[head->data] ;
if(starts(str)){
    
        if (likes  && LikedSong.find(head->data)==LikedSong.end()) {
            int yes;
            cout << "Like this song? (1 for Yes, 0 for No): ";
            cin >> yes;
            if (yes) {
                LikedSong.insert(head->data);
                cout<<head->data<<endl;
                Song s(4, head->data); // Add to Likes
            }
        }
    }

       cout << "Prev (1), Next (2), Exit (-1): ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            head = head->back;
        } else if (choice == 2) {
            head = head->next;
        } else {
            break;
        }
    } while (true);
    
}

void searchSong(){
     int id;
    string name;
   cout << "\n--- SEARCH FOR A SONG ---" << endl;
cout << "Enter the name of the song to search: ";
cin >> name;
    
   id=SongName[name];
    Song s;
    auto song=s.findSong(id);
    
if (song)
    cout << "Song found: " << SongList[song->id] << endl;
else
    cout << "Sorry, the song '" << name << "' was not found." << endl;
}
void playSongs(){
    
    cout << "\n--- PLAY SONGS ---" << endl;
cout << "Enter the style you want to listen to:" << endl;
cout << "1: Bollywood" << endl;
cout << "2: Hollywood" << endl;
cout << "3: Tollywood" << endl;
cout << "4: Liked Songs" << endl;
cout << "5: Mixed Playlist (All Styles)" << endl;
cout << "Your choice: ";
        
    bool likes=1;
        int ids;
        cout<<"Enter Style You Want to Listen"<<endl;
            cin>>ids;
         ListNode *head=new ListNode(0);
        if(ids==1 ||ids==2 ||ids==3 || ids==4){
            Song *s=RootCollection[ids].first;
           
            ListNode* tail = head;  
            s->fetchSongs(s, tail);
            head=head->next;
            tail=head;
            while(tail->next){
                
                tail=tail->next;
            }
            cout<<endl;
            tail->next=head;
            head->back=tail;
           
            
           

        }
       else {
    Song *s1 = RootCollection[1].first; // Bollywood root
    Song *s2 = RootCollection[2].first; // Hollywood root
    Song *s3 = RootCollection[3].first; // Tollywood root;

    // Create dummy heads for each style's list
    ListNode *head1 = new ListNode(0);
    ListNode *head2 = new ListNode(0);
    ListNode *head3 = new ListNode(0);

    // Fetch songs for each style
    ListNode *tail1 = head1, *tail2 = head2, *tail3 = head3;
   
    s3->fetchSongs(s3, tail3);
    s2->fetchSongs(s2, tail2);
     s1->fetchSongs(s1, tail1);

    // Move heads to the first actual node (skip dummy nodes)
    head1 = head1->next;
    head=head1;
    head2 = head2->next;
    head3 = head3->next;

    // Link the lists together to form a circular linked list
    ListNode *current = head1;

    // Traverse to the end of head1 and link it to head2
    while (current->next != nullptr)
        current = current->next;
    current->next = head2;
    head2->back = current;

    // Traverse to the end of head2 and link it to head3
    current = head2;
    while (current->next != nullptr)
        current = current->next;
    current->next = head3;
    head3->back = current;

   
    current = head3;
    while (current->next != nullptr)
        current = current->next;
    current->next = head1;
    head1->back = current;
}

        if(ids==4)
            likes=0;
        displaySongs(head,likes);
        likes=1;
       
}


int main() {
    cout<<"========== MUSIC RECOMMENDATION SYSTEM =========="<<endl;
    
    RootCollection[1].first=new Song(1,"Bollywood"); 
    RootCollection[2].first=new Song(2,"Hollywood");
    RootCollection[3].first=new Song(3,"Tollywood");
    RootCollection[4].first=new Song(4,"Likes");;
    SongList[10]="START B-O-L-L-Y-W-O-O-D";
    SongList[20]="START H-O-L-L-Y-W-O-O-D";
    SongList[30]="START T-O-L-L-Y-W-O-O-D";
    SongList[40]="START L-I-K-E-D S-O-N-G-S";
    int id;
    while(true){
        cout<<"Please select an option from the menu below:"<<endl;
        cout<<"0: Add new songs"<<endl;
        cout<<"1: Delete a song"<<endl;
        cout<<"2: Play songs "<<endl;
        cout<<"3: Search for a song by name"<<endl;
        cout<<"================================================="<<endl;
        
        

    cin>>id;
    if(id==0){
       
           
        addSongs();
        
            
    }
    else if(id==1)
        deleteSongs();
    else if(id==2)
    {
        playSongs();
        
    }
    else if(id==3){
        searchSong();
    }
    else{
        break;
   
    }
    cout<<endl;
}
cout << "\nThank you for using the Music Recommendation System!" << endl;
cout << "Goodbye!" << endl;
    

    return 0;
}
