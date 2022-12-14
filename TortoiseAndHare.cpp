// cycle detection in linked list

bool cycle(head){
  if(!head || !head.next){
    return false;
  }
  Vertex tortoise = head;
  Vertex hare = head.next; //can also set hare to head i.e. tortoise and hare start same point, no difference
  while(hare && hare.next){
    if(tortoise==hare){
      return true;
    }
    tortoise = tortoise.next;
    hare = hare.next.next;
  }
  return false;
}
