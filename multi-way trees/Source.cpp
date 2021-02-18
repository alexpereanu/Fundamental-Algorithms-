typedef struct nd {
	int id;
	Data *data;
	struct tm *_parent;
	struct tm *_child[7];
} Node;


Node* findNode(int id, Node *tree) {
	Node *p = tree;
	if (id == p->_id)
		return p;
	for (int i = 0; i < 7; i++) {
		if (id == p->_child[i]->_id) {
			p = p->_child[i];
			break;
		}
		else if (p->_child[i] != NULL) {
			findNode(id, p->_child[i]);
		}
	}

	return p;
}