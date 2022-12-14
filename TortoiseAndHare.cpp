// cycle detection in linked list

bool cycle(head){
  if(!head || !head.next){
    return false;
  }
  Vertex* tortoise = head;
  Vertex* hare = head.next;
  while(hare && hare.next){
    if(tortoise==hare){
      return true;
    }
    tortoise = tortoise.next;
    hare = hare.next.next;
  }
  return false;
}
