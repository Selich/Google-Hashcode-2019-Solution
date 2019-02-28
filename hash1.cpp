#include <bits/stdc++.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>

#define mp make_pair
#define mt make_tuple
#define f first
#define s second
#define pb push_back
#define all(x) (x).begin() , (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)n; ++i)
#define for1(i, n) for (int i = 1; i < (int)n; ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;




class Picture{


public:
    int id1;
    int id2;
    int numOfTags;
    char pos;
    vector<string> arrOfTags;

    Picture() {};
    Picture(int idd, int num,char poss ) {
        id1 = idd;
        id2 = idd;
        numOfTags = num;
        pos = poss;
    }
    // V
    Picture(int idd,int iddd,int num,char poss ) {
        id1 = idd;
        id2 = iddd;
        numOfTags = num;
        pos = poss;
    }


    void addTags(string str){
        arrOfTags.push_back(str);

    }

    char getPos(){
        return pos;
    }


};

vector<Picture> sortPic(vector<Picture> pics){
    sort(pics.begin(), pics.end(), [=] (Picture a, Picture b) -> bool {
        return a.numOfTags < b.numOfTags;
    });
    return pics;
}


vector<pair<Picture,Picture>> findLess(vector<Picture> pics){
    int k  = 0;
    int minid = 0;
    int min = INT_MAX;
    vector<pair<Picture,Picture>> result;
    pair<int,int> minpair;
     forn(i,pics.size()){
        Picture pic1 = pics[i];
        for(auto j = i; j < pics.size(); j++)
        {
            Picture pic2 = pics[j];
            for(string tag : pic2.arrOfTags){
                if(binary_search(pic1.arrOfTags.begin(), pic1.arrOfTags.end(),tag)){
                    k++;
                } else {
                    continue;
                };
            }
            if(min > k) {
                min = k;
                minid = j;

            }
        }
        result.push_back({pics[i],pics[minid]});
        pics.erase(pics.begin() + i);
        pics.erase(pics.begin() + minid);

    }
    return result;
}

Picture uniteTags(pair<Picture,Picture> pics){
    Picture sec = pics.second;
    Picture first = pics.first;
    vector<string> res;
    Picture* pec;
    pec = new Picture(sec);

    for(string tagx : first.arrOfTags){
            if(binary_search(sec.arrOfTags.begin(), sec.arrOfTags.end(), tagx)){
                pec->addTags(tagx);
            }
    }
    sort(pec->arrOfTags.begin() , pec->arrOfTags.end());
    pec->id1 = pec->id2;
    return *pec;


}

vector<Picture> addResulting(vector<pair<Picture,Picture>> pics){
    vector<Picture> res;
    for(auto i = 0; i < pics.size(); i++)
    {
        res.push_back(uniteTags(pics[i]));


    }
    return res;
    
}


vector<Picture> fillSlides(vector<Picture> vp, vector<Picture> hp){
    vector<Picture> res;
    res.reserve(vp.size() + hp.size());
    res.insert(res.end(), vp.begin(), vp.end());
    res.insert(res.end(), hp.begin(), hp.end());

    return sortPic(res);


}



vector<int> filterSlide(vector<Picture> arr){
    
    vector<int> res;

    int k = 0;
    res.push_back(arr[0].id1);
    forn(i,arr.size()){
        vector<string> arrTagsx = arr[i].arrOfTags;
        for(int j = i; j = arr.size(); j++){
            vector<string> arrTagsy = arr[j].arrOfTags;
            for(string tagx : arrTagsx){
                for(string tagy : arrTagsy){
                    k = abs((int)arrTagsx.size() - (int)arrTagsy.size());
                    int rep = k / 6;
                    int b = 0;
                    if(rep == b) {
                        res.push_back(arr[j].id1);
                        break;

                    };
                    if(tagx == tagy) b++;
                }
            }

        }

    }
    return res;
    // 0.6
    // 0.3




}



Picture findMaxPic(vector<Picture> pics){
    Picture max;
    max.numOfTags = -1;
    for(Picture pic : pics){
        if(max.numOfTags < pic.numOfTags){
            max = pic;
        }
    }

    return max;

}


vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

int main(){


    vector<string> collection;
    vector<Picture> pictures;
    vector<Picture> vp;
    vector<Picture> hp;

    map<string,int> mapp;
    map<string,int>::iterator it;



    string str;
     while(getline(cin, str)){
         collection.push_back(str);
     }



    for(int i = 1; i < collection.size(); i++)
    {
        vector<string> l =  split(collection[i], " ");
        char c =  *l[0].c_str();
        int r = stoi(l[1]);
        //fscanf(collection[i], "%c %d", &c , &r);
        cin >> c >> r ;
        cout << c << " " << r << endl;
        if(c == 'V'){
            Picture* pic = new Picture(i,r,c);
            for(auto j = l.size() + 2; j < r; j++){
                string str;
                cin >> str;
                pic->addTags(str);
           }
           vp.push_back(*pic);

        } else if(c == 'H'){
            Picture* pic = new Picture(i,r,c);
            for(auto j = l.size() + 2; j < r; j++){
                string str;
                cin >> str;
                pic->addTags(str);
           }
           hp.push_back(*pic);
        }
    }

    sortPic(vp);
    sortPic(hp);

    vector<pair<Picture,Picture>> resp = findLess(vp);
    vector<Picture> vo;
    vo = addResulting(resp);
    vector<Picture> res = fillSlides(vo,hp);
    vector<int> resin = filterSlide(res);


    cout << res.size() << endl;

    for(int num : resin){
        cout << num << endl;;
    }


}