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

    Iterator add(Iterator old, int i){
       Iterator now = old + i;
       while(now > last){
           now -= size;
       }
       return now;
    }

    Iterator sub(Iterator old, int i){
        Iterator now = old - i;
        while (now < first) {
            now += size;
        }
        return now;
    }
    int sub(Iterator first, Iterator second){
        int now = first - second;
        while(now < 0){
            now += size;
        }
        return now;
    }
};