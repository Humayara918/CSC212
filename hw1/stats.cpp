#include "stats.h"
#include <iostream>
#include <cassert>
using namespace std;

 namespace main_savitch_2C {
     statistician::statistician (){
         m_total=0;
         m_count=0;
     }

     void statistician::next(double r){
         if (m_count !=0){
             m_total +=r;
             
            if (r< minimum()){
                m_tinyest=r;
            }
            if (r> maximum()){
                m_largest=r;
            }
         }
         else{
        m_total = r;
		m_tinyest = r;
		m_largest = r;
         }
         m_count++;
         
     }

     void statistician::reset(){
         m_count=0;
         m_total=0;
         m_tinyest=0;
         m_largest=0;
     }

     int statistician::length()const{
        return m_count;//number of times next(r) has benne activated


     }
     double statistician::sum()const{
         return m_total;
     }
     double statistician::mean()const{
         assert(length()>0);
         return m_total/m_count;
         
     }
     double statistician::minimum()const{
         assert(length()>0);
         return m_tinyest;
     }
      double statistician::maximum()const{
         assert(length()>0);
         return m_largest;
     }

     statistician operator +(const statistician& s1, const statistician& s2){
         if(s1.length()<=0){
             return s2;
         }
         if(s2.length()<=0){
             return s1;
         }
          statistician value;
          value.m_count= s1.length()+s2.length();
          value.m_total= s1.m_total + s2.m_total;
          if(s1.minimum()<s2.minimum()){
              value.m_tinyest=s1.minimum();
          }
          else value.m_tinyest=s2.minimum();
          if (s1.maximum() > s2.maximum()){
		value.m_largest = s1.maximum(); 
          }
	else value.m_largest = s2.maximum();
	return value;

     }
     statistician operator *(double scale, const statistician&s){
         if(s.length()==0){
             return s;
         }
          statistician value;
          value.m_count= s.length();
          value.m_total= scale * s.m_total; 
          value.m_largest= scale < 0 ? scale * s.minimum():scale * s.maximum();
          value.m_tinyest= scale < 0 ? scale * s.maximum():scale * s.minimum();
          
          return value;
          
     }
        bool operator ==(const statistician& s1, const statistician& s2){
            if(s1.length()==0 && s2.length()==0) {
                return true;
            }
            if(s1.length()!=s2.length()){
                return false;
            }
            if(s1.length()>0 && s2.length()>0){
                return (
            (s1.mean() == s2.mean()) &&
		    (s1.sum() == s2.sum())   &&
			(s1.minimum() == s2.minimum()) &&
			(s1.maximum() == s2.maximum())  );
                
            }

            return false;
        }

 }