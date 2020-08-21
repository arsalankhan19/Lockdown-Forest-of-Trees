#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<map>
using namespace std;

struct node
{
	int data;
	node *left;
	node *right;
};

node *get_node(int item)
{
	node *temp = new node;

	temp->data = item;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

node *construct_tree(node *root, int i, int arr[], int n)
{
	if (i >= n)
		return root;

	node *temp = get_node(arr[i]);

	root = temp;

	root->left = construct_tree(root->left, 2 * i + 1, arr, n);
	root->right = construct_tree(root->right, 2 * i + 2, arr, n);

	return root;
}

void pre_order(node *root)
{
	if (root == NULL)
		return;

	cout << root->data << " ";
	pre_order(root->left);
	pre_order(root->right);
}

void post_order(node *root)
{
	if (root == NULL)
		return;

	post_order(root->left);
	post_order(root->right);
	cout << root->data << " ";
}

node *parent_of_value(node *root, int value)
{
	if (root == NULL)
		return NULL;

	if (root->left == NULL && root->right == NULL)
		return NULL;

	if (root->right == NULL && root->left != NULL) {
		if (root->left->data == value) {
			cout << "hello" << endl;
			return root;
		}
	}

	if (root->left == NULL && root->right != NULL)
		if (root->right->data == value)
			return root;

	if (root->left != NULL && root->right != NULL) {
		if (root->left->data == value || root->right->data == value)
			return root;
	}

	node *temp_1 = parent_of_value(root->left, value);

	if (temp_1 != NULL)
		return temp_1;

	return parent_of_value(root->right, value);

}

int get_level(node *root, int data, int level)
{
	if (root == NULL)
		return 0;

	//cout<<root->data<<endl;
	if (root->data == data)
		return level;

	int left_level = get_level(root->left, data, level + 1);

	if (left_level != 0)
		return left_level;

	return get_level(root->right, data, level + 1);

}

void print_cousins(node *root, node *par, int level, int temp)
{
	if (root == NULL)
		return;

	if (temp == level && root->data != par->data)
	{
		if (root->left != NULL)
			cout << root->left->data << " ";
		if (root->right != NULL)
			cout << root->right->data << " ";
	}

	print_cousins(root->left, par, level, temp + 1);
	print_cousins(root->right, par, level, temp + 1);

}

int is_sum_tree(node *root)
{
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL)
		return root->data;

	//int sum = (is_sum_tree(root->left) + is_sum_tree(root->right));

	int ls = is_sum_tree(root->left);
	int rs = is_sum_tree(root->right);

	int sum = ls + rs;

	if (sum == root->data)


		//sum += root->data;

		return sum;
}

node *LCA(node *root, int n1, int n2)
{
	if (root == NULL)
		return NULL;

	if (root->data == n1 || root->data == n2)
		return root;

	node *left_LCA = LCA(root->left, n1, n2);
	node *right_LCA = LCA(root->right, n1, n2);

	if (left_LCA && right_LCA) return root;

	return (left_LCA != NULL) ? left_LCA : right_LCA;
}

void morris_trav(node *root)
{
	node *current = root, *pre;

	if (root == NULL)
		return;

	while (current != NULL)
	{
		if (current->left == NULL)
		{
			cout << current->data << " ";
			current = current->right;
		}

		else
		{
			pre = current->left;

			while (pre->right != NULL && pre->right != current)
				pre = pre->right;

			if (pre->right == NULL)
			{
				pre->right = current;
				current = current->left;
			}

			//breaking the extra links
			else
			{
				pre->right = NULL;
				cout << current->data << " ";
				current = current->right;
			}

		}
	}
}

void spiral_trav(node *root, int level)
{
	stack<node*> s1;
	stack<node*> s2;

	s1.push(root);

	while (!s1.empty() || !s2.empty())
	{
		while (!s1.empty())
		{
			node *temp = s1.top();
			s1.pop();
			cout << temp->data << " ";

			if (temp->right)
				s2.push(temp->right);

			if (temp->left)
				s2.push(temp->left);

		}

		while (!s2.empty())
		{
			node *temp = s2.top();
			s2.pop();
			cout << temp->data << " ";

			if (temp->left)
				s1.push(temp->left);

			if (temp->right)
				s1.push(temp->right);
		}
	}
}

int height(node *root)
{
	if (root == NULL)
		return 0;

	return (height(root->left) > height(root->right) ? height(root->left) : height(root->right)) + 1;
}

void print_spiral(node *root, int level, bool ltr)
{
	if (root == NULL)
		return;

	if (level == 1)
		cout << root->data << " ";

	if (level > 1)
	{
		if (ltr)
		{
			print_spiral(root->left, level - 1, ltr);
			print_spiral(root->right, level - 1, ltr);
		}

		else
		{
			print_spiral(root->right, level - 1, ltr);
			print_spiral(root->left, level - 1, ltr);
		}
	}
}

void rec_spiral_order(node *root)
{
	int h = height(root);
	bool ltr = false;
	int i;

	for (i = 1; i <= h; i++) {
		print_spiral(root, i, ltr);

		ltr = !ltr;
	}
}

int children_sum(node *root)
{
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL)
		return root->data;

	int ls = children_sum(root->left);
	int rs = children_sum(root->right);

	if (root->data < (ls + rs) || root->data == (ls + rs))
		root->data = (ls + rs);

	else if (root->data > (ls + rs)) {
		root->right->data = root->data - root->left->data;
		children_sum(root);
	}

	return root->data;
}

void prints(node *root, int level, bool ltr)
{
	if (root == NULL)
		return;

	if (level == 1)
		cout << root->data << " ";

	if (level > 1)
	{
		if (ltr)
			prints(root->left, level - 1, ltr);

		else
			prints(root->right, level - 1, ltr);

	}

}

void print_extreme_nodes(node *root)
{
	int h = height(root);

	int i;
	bool ltr = false;

	for (i = 1; i <= h; ++i)
	{
		prints(root, i, ltr);

		ltr = !ltr;
	}
}

void ite_extreme_nodes(node *root)
{
	stack<node*> s1;
	stack<node*> s2;

	s1.push(root);
	int flag1 = 0, flag2 = 0, flag1_ka_flag = 1, flag2_ka_flag = 1;

	while (!s1.empty() || !s2.empty())
	{
		while (!s1.empty())
		{
			if (flag1_ka_flag) {
				flag1 = 0;
				flag1_ka_flag = 0;
			}

			node *temp = s1.top();

			if (flag1 == 0)
			{
				cout << temp->data << " ";
				flag1 = 1;
			}

			s1.pop();

			if (temp->right)
				s2.push(temp->right);

			if (temp->left)
				s2.push(temp->left);
		}

		flag1_ka_flag = 1;

		while (!s2.empty())
		{
			if (flag2_ka_flag) {
				flag2 = 0;
				flag2_ka_flag = 0;
			}

			node *temp = s2.top();

			if (flag2 == 0)
			{
				cout << temp->data << " ";
				flag2 = 1;
			}


			s2.pop();

			if (temp->left)
				s1.push(temp->left);

			if (temp->right)
				s1.push(temp->right);
		}

		flag2_ka_flag = 1;
	}
}

void diagonal_trav(node *root)
{
	stack<node*> s1;
	stack<node*> s2;

	s1.push(root);

	while (!s1.empty() || !s2.empty())
	{
		while (!s1.empty())
		{
			node *temp = s1.top();
			s1.pop();

			cout << temp->data << " ";

			if (temp->right)
				s1.push(temp->right);

			if (temp->left)
				s2.push(temp->left);
		}

		while (!s2.empty())
		{
			node *temp = s2.top();
			s1.push(temp);
			s2.pop();
		}
	}
}

void vertical_sum(node *root, int vertical_line, map<int, int> &m)
{
	if (!root)
		return;

	vertical_sum(root->left, vertical_line + 1, m);

	m[vertical_line] += root->data;

	vertical_sum(root->right, vertical_line - 1, m);
}

void mul_of_sum_of_data(node *root, int level, map<int, int> &m)
{
	if (!root)
		return;

	if (!root->left && !root->right) {
		m[level] += root->data;
		return;
	}

	mul_of_sum_of_data(root->left, level + 1, m);
	mul_of_sum_of_data(root->right, level + 1, m);
}

int maxi = INT8_MIN;
void max_diff(node *root, int a[], int i)
{
	if (!root)
		return;

	a[i] = root->data;

	if (!root->left && !root->right)
	{
		for (int j = i; j > 0; j--)
		{
			for (int k = j - 1; k >= 0; k--)
			{
				if ((a[k] - a[j]) > maxi)
				{
					maxi = a[k] - a[j];
					cout << maxi << " ";
				}
			}
		}

		return;
	}

	max_diff(root->left, a, i + 1);
	max_diff(root->right, a, i + 1);

}

int min(int a, int b)
{
	if (a < b)
		return a;

	else
		return b;
}

int max(int a, int b)
{
	if (a < b)
		return b;

	else
		return a;
}

int max_diff_n(node *root, int *res)
{
	if (!root)
		return INT8_MAX;

	if (!root->left && !root->right)
		return root->data;

	int temp = min(max_diff_n(root->left, res), max_diff_n(root->left, res));

	*res = max(*res, root->data - temp);

	return min(root->data, temp);
}

void top_view(node *root, int level, int height, map<int, pair<int, int>> &m)
{
	if (!root)
		return;

	if (!root->left && !root->right)
		return;



	//m[level].push_back(root->data);
	top_view(root->left, level - 1, height + 1, m);
	top_view(root->right, level + 1, height + 1, m);

}

bool remove_dist_k(node *root, int k, int level)
{
	if (!root)
	{
		if (level < k)
			return true;

		else
			return false;
	}

	bool lst = remove_dist_k(root->left, k, level + 1);
	if (lst)
		root->left = NULL;

	bool rst = remove_dist_k(root->right, k, level + 1);
	if (rst)
		root->right = NULL;

	if (lst && rst)
		return true;

	else
		return false;

}

void reverse_level(node *root, bool even, int h, stack<int> &v, bool fill, bool feed)
{
	if (h == 1 && even && fill)
	{
		v.push(root->data);

		return;
	}

	if (h == 1 && even && feed)
	{
		int temp = v.top();
		root->data = temp;
		v.pop();

		return;
	}

	if (even && fill)
	{
		reverse_level(root->right, even, h - 1, v, fill, feed);
		reverse_level(root->left, even, h - 1, v, fill, feed);
	}

	if (even && feed)
	{
		reverse_level(root->right, even, h - 1, v, fill, feed);
		reverse_level(root->left, even, h - 1, v, fill, feed);
	}
}

void reverse_alternate_levels(node *root, int h)
{
	bool even = false, fill = true, feed = false;
	int i;
	stack<int> s;

	for (int i = 1; i <= h; i++)
	{
		reverse_level(root, even, i, s, fill, feed);
		fill = !fill;
		feed = !feed;
		reverse_level(root, even, i, s, fill, feed);

		fill = !fill;
		feed = !feed;
		even = !even;
	}
}

int dstnc_frm_root(node *root, int target, int level)
{
	if (!root)
		return 0;

	if (root->data == target)
		return level;

	return max(dstnc_frm_root(root->left, target, level + 1), dstnc_frm_root(root->right, target, level + 1));
}

bool lca(node *root, int t1, int t2, int *l)
{
	if (!root)
		return false;

	if (root->data == t1 || root->data == t2)
		return true;

	bool lst = lca(root->left, t1, t2, l);
	bool rst = lca(root->right, t1, t2, l);

	if (lst && rst)
		*l = root->data;

	if (lst || rst)
		return true;
}

int lca_dstnc(node *root, int t1, int t2)
{
	if (!root)
		return 0;

	int lca_value;
	lca(root, t1, t2, &lca_value);

	return dstnc_frm_root(root, lca_value, 0);
}

int find_distance(node *root, int t1, int t2)
{
	if (!root)
		return 0;

	return (dstnc_frm_root(root, t1, 0)) + (dstnc_frm_root(root, t2, 0)) - (2 * lca_dstnc(root, t1, t2));
}

void print_node_down(node *root, int k)
{
	if (!root || k < 0)
		return;

	if (k == 0)
		cout << root->data << " ";

	print_node_down(root->left, k - 1);
	print_node_down(root->right, k - 1);
}

int print_k_distance_node(node *root, node *target, int k)
{
	if (!root)
		return -1;

	if (root == target)
	{
		print_node_down(root, k);
		return 1;
	}

	int dl = print_k_distance_node(root->left, target, k); // target se kitni dur h
	// 0 dur h to dl=0
	if (dl != -1)
	{
		if (dl == k)
			cout << root->data << " ";

		else
			print_node_down(root->right, k - dl - 1); //-dl isliye ki kitni upar aa gye
		//-1 isliye ki right me ja rahe h

		return 1 + dl;
	}

	int dr = print_k_distance_node(root->right, target, k);

	if (dr != -1)
	{
		if (dr == k)
			cout << root->data << " ";

		else
			print_node_down(root->left, k - dr - 1);

		return 1 + dr;
	}

	return -1;
}

bool burn_tree(node *root, node *source, queue<node*> &q)
{
	if (!root)
		return false;

	if (root == source)
	{
		cout << root->data << " ";
		q.push(root->left);
		q.push(root->right);

		return true;
	}

	if (burn_tree(root->left, source, q))
	{
		cout << root->data << " ";

		burn_tree(root->right, source, q);
	}
}

int levels(node *root, int key, int level)
{
	if (!root)
		return 0;

	if (root->data == key)
	{
		//cout<<level<<endl;
		return level;
	}

	int ll = levels(root->left, key, level + 1);
	if (ll != 0) {
		//cout<<ll<<endl;
		return ll;
	}

	int rl = levels(root->right, key, level + 1);

	if (rl != 0)
		return rl;

	return 0;
}

void right_node_utils(node *root, int l, int key, bool *dec)
{
	if (!root)
		return;

	if (l == 1)
	{
		if (root->data == key)
		{
			*dec = !*dec;
			return;
		}

		else if (root->data != key && *dec == true) {
			cout << root->data << endl;
			*dec = !*dec;
			return;
		}

	}

	right_node_utils(root->left, l - 1, key, dec);
	right_node_utils(root->right, l - 1, key, dec);

}

void right_node(node *root, int key)
{
	int l = levels(root, key, 1);

	bool temp = false;
	right_node_utils(root, l, key, &temp);
}

void left_and_leaves(node *root)
{
	if (!root)
		return;

	static bool flag = true;
	static int count = 0;

	if (flag == true)
		cout << root->data << " ";

	if (!root->left && !root->right)
	{
		if (count != 0)
			cout << root->data << " ";

		flag = false;
		count++;

		return;
	}

	left_and_leaves(root->left);
	left_and_leaves(root->right);

}

void right_boundary(node *root)
{
	static node *temp = root;

	if (!root->left && !root->right)
		return;

	right_boundary(root->right);

	if (temp != root)
		cout << root->data << " ";
}

void anticlockwise_trav(node *root)
{
	left_and_leaves(root);
	right_boundary(root);
}

int sum_tree(node *root)
{
	if (!root)
		return 0;

	if (!root->left && !root->right)
	{
		int temp = root->data;
		root->data = 0;
		return temp;
	}

	int lst = sum_tree(root->left);
	int rst = sum_tree(root->right);

	int temp_1 = lst + rst + root->data;
	root->data = lst + rst;

	return temp_1;
}

int main()
{
	node *root;
	root = NULL;

	int n, value;
	cin >> n;

	int arr[n];

	cout << "Enter the elements:" << endl;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	root = construct_tree(root, 0, arr, n);

	pre_order(root);
	cout << endl;

	// node* root = newNode(10);
//    root->left = newNode(12);
//    root->right = newNode(13);

//  	root->left->left = newNode(70);
//  	root->left->right = newNode(72);
//    root->right->left = newNode(14);
//    root->right->right = newNode(15);

//    root->left->left->left = newNode(40);
//  	root->left->left->right = newNode(45);
//    root->right->left->left = newNode(21);
//    root->right->left->right = newNode(22);
//    root->right->right->left = newNode(23);
//    root->right->right->right = newNode(24);

//    root->right->left->left->left = newNode(1);
//    root->right->left->left->right = newNode(2);
//    root->right->left->right->left = newNode(3);
//    root->right->left->right->right = newNode(4);

//    root->right->left->left->left->left = newNode(51);
//    root->right->left->left->left->right = newNode(52);

//    root->right->left->left->right->left = newNode(53);
//    root->right->left->left->right->right = newNode(54);


	// 1. PRINT COUSINS
	// cout<<"Enter the node for cousins:"<<endl;
	// cin>>value;

	// int level = get_level(root,value,1);
	// 	cout<<level<<endl;

	// node *par_v = parent_of_value(root,value);

	//  if(par_v != NULL)
	//  	cout<<par_v->data<<endl;

	//  else if(par_v == NULL)
	//  	cout<<"NULL"<<endl;

	// print_cousins(root,par_v,level-1,1);

	// 2. SUM TREE
	// int sum = is_sum_tree(root);
	// if(root->data = sum - root->data)
	// 	cout<<"YES"<<endl;

	// else
	// 	cout<<"NO"<<endl;

	// 3. LOWEST COMMON ANCESTOR
	// cout<<"Enter the node values:"<<endl;
	// int n1,n2;
	// cin>>n1>>n2;
	// node *ancesotr = LCA(root,n1,n2);

	// cout<<ancesotr->data<<endl;

	// 4. MORRIS TRAVERSAL
	//morris_trav(root);

	// 5.ITERATIVE SPIRAL ORDER
	//spiral_trav(root,1);

	// 6.RECURSIVE SPIRAL ORDER
	//rec_spiral_order(root);

	// 7.Children sum property
	//int c = children_sum(root);

	// 8.EXTREME NODES
	//print_extreme_nodes(root);

	// 9.EXTREME NODES ITERATIVE
	//ite_extreme_nodes(root)

	// 10.Diagonal traversal
	//diagonal_trav(root);

	// 11.Vertical Sum
	// map<int,int> m;
	// vertical_sum(root,0,m);

	// map<int,int> :: iterator it;

	// for(it = m.begin();it!=m.end();it++)
	// {
	// 	cout<<it->first<<" "<<it->second<<" ";
	// 	cout<<endl;
	// }

	// 12.Multiplication of sum of data of leaves
	// mul_of_sum_of_data(root,0,m);

	// map<int,int> :: iterator it;

	// for(it = m.begin();it!=m.end();it++)
	// {
	// 	cout<<it->first<<" "<<it->second<<" ";
	// 	cout<<endl;
	// }

	// 13.Diff between a node and its ancestor // > O(n)
	// int h = height(root);
	// int a[h];
	// max_diff(root,a,0);
	// cout<<maxi<<endl;

	// 14.Diff between a node and its ancestor // O(n)
	// int res = INT8_MIN;
	// max_diff_n(root,&res);
	// cout<<res<<endl;

	// 15.Top View
	// map<int,pair<int,int>> m;
	// top_view(root,0,1,m);

	// map<int,vector<int,int>> :: iterator it;

	// for(it = m.begin();it != m.end();it++)
	// {

	// }

	// 16.Remove nodes <k
	// int k;
	// cin >> k;

	// if(remove_dist_k(root,k,0)){
	// 	root = NULL;
	// 	cout<<"NULL"<<endl;
	// }

	// 17.Reverse alternate levels of a perfect binary tree(with auxiliary space)
	// reverse_alternate_levels(root,h);
	// (without auxiliary space)
	// we can pass (root->left,root->right)

	// 18.Distance between two nodes of a Binary Tree
	// cout<<find_distance(root,8,15)<<endl;

	// 19.Print all nodes that are at distance k from a leaf node
	//

	// 20.Node at k distance from given node
	// node *target = root->left->right;
	// print_k_distance_node(root,target,3);

	// 21.Burn the binary tree starting from the target node
	// Seperate code

	// 22.Next right node of a given key
	// int key;
	// cin >> key;

	// right_node(root,key);

	// 23.Anticlockwise boundary traversal of BT
	// anticlockwise_trav(root);

	// 24.Converting to Sum tree
	//   sum_tree(root);
	//   pre_order(root);

}