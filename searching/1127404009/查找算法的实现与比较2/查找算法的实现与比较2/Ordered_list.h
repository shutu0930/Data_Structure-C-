
class Ordered_list:public List<Record>{
public:
	Ordered_list();
	Error_code insert(const Record &data);
	Error_code insert(int position,const Record &data);
	Error_code replace(int position,const Record &data);
};

Ordered_list::Ordered_list()
{
	count=0;
}

Error_code Ordered_list::insert(const Record &data)
{
	int s=size();
	int position;
	for(position=0;position<s;position++){
		Record list_data;
		retrieve(position,list_data);
		if(data>=list_data)break;
	}
	return List<Record>::insert(position,data);
}
Error_code Ordered_list::insert(int position,const Record &data)
{
	Record list_data;
	if (position > 0) {
		retrieve(position - 1, list_data);
		if (data < list_data)
			return fail;
	}
	if (position < size()) {
		retrieve(position, list_data);
		if (data > list_data)
			return fail;
	}
	return List<Record>::insert(position, data);
}

Error_code Ordered_list::replace(int position,const Record &data)
{
	Record list_data;
	if (position > 0) {
		retrieve(position - 1, list_data);
		if (data < list_data)
			return fail;
	}
	if (position < size()) {
		retrieve(position, list_data);
		if (data > list_data)
			return fail;
	}
	return List<Record>::replace(position, data);
}