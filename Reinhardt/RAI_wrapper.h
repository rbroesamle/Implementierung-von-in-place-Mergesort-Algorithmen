//
// Created by jonas on 25.12.2018.
//
template<typename Iterator>
class RAI_wrapper {

    Iterator first;
    Iterator last;
    int size;

    RAI_wrapper(Iterator first, Iterator last) : first(first), last(last){
        size = last - first + 1;
    };

    Iterator add(Iterator old, unsigned int i){
       Iterator now = old + (i % size);
       if(now > last){
           now -= size;
       }
       return now;
    }

    Iterator sub(Iterator old, unsigned int i){
        Iterator now = old - (i % size);
        if(now < first) {
            now += size;
        }
        return now;
    }
    int sub(Iterator first, Iterator second){
        int now = first - second;
        if(now < 0){
            now += size;
        }
        return now;
    }
};