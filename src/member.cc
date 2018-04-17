#include "member.h"

#include <queue>

#include "database.h"

namespace algdb {

void Member::DumpConnections() {
  std::cout << "(" << member_id << ")";
  for (auto &m : connecting_members) {
    auto conn = m.second;
    std::cout << "->" << conn.dst->member_id << 
      "(" << conn.group->group_id << ")";
  }
  std::cout << "\n";
}

void Member::PathToMemberBFS(uint64_t dst_member_id) {
  // Fill in your code here.
  //verticies are members, edges are connecting member 
  std::queue<Member*> Q;
  Member *source = this;
  Member *u;
  //MemberConnection *v;
  source->color = COLOR_GRAY;
  source->key = 0;
  //empty queue
  while(!Q.empty()){
    Q.pop();
  }
  
  Q.push(source);
  while(!Q.empty()){
    u=Q.front();
    Q.pop();
        
    //for each vertex that is connected to u
    for ( auto it = u->connecting_members.begin(); it != u->connecting_members.end(); ++it ){
      if(it->second.dst->color == COLOR_WHITE){
        it->second.dst->color = COLOR_GRAY;
        it->second.dst->key = u->key+1;
        it->second.dst->parent = u;
        Q.push(it->second.dst);
      }
    }
    u->color=COLOR_BLACK;
  }
}

void Member::PathToMemberIDDFS(uint64_t dst_member_id) {
  // Fill in your code here

  Member* source =this;
  for(int i =0; i< 99; i++){
    DLS(source, dst_member_id, i);
  }
}
  
Member* Member::DLS(Member* dst, uint64_t dst_member_id, double key){
  Member* found;
  if(dst->member_id == dst_member_id && key ==0){
    return dst;
  }
  
  if(key > 0){
    for ( auto it = dst->connecting_members.begin(); it != dst->connecting_members.end(); ++it ){
      it->second.dst->parent = dst;
      found =DLS(it->second.dst, dst_member_id, key-1);
      if(found != NULL){
        return found;
      }
    }
  }
  return NULL;
  
}


void Member::PrintPath(Member* dst) {
  Member *curr = dst;
  while(curr && curr != this) {
    std::cout << curr->member_name << " <- ";
    curr = curr->parent;
  }
  std::cout << this->member_name << "\n";
}

}
