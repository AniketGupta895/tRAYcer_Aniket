#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

class hittable_list : public hittable{
    vector<shared_ptr<hittable> > objects;
public:
    hittable_list(){};
    hittable_list(shared_ptr<hittable> const& object){
        add(object);
    }

    void add(shared_ptr<hittable> object){
        objects.push_back(object);
    }

    void clear(){
        objects.clear();
    }

    bool hit(ray const& lightray, interval ray_interval, hit_record& rec) const override{
        hit_record temprec;
        bool hit_an_object = false;
        interval temp_interval = ray_interval;
        
        for (int i = 0; i < objects.size(); i++){
            if (objects[i]->hit(lightray, temp_interval, temprec)){
                hit_an_object = true;
                temp_interval.max = temprec.t;
                rec = temprec;
            }
        }
        return hit_an_object;
    }

    ~hittable_list() override = default;
};

#endif