#include "Request.h"
#include "definitions.h"
#include <cstdlib>
#include <limits>

Request::Request(void) :
subject(vector<float>(WORDSIZE,0)), object(vector<float>(WORDSIZE,0)), predicate(vector<float>(WORDSIZE,0))
{
  predicate=vector<float>(WORDSIZE,0);
  subject=vector<float>(WORDSIZE,0);
  object=vector<float>(WORDSIZE,0);
  for(unsigned int i=0;i<WORDSIZE;i++)
  {
    predicate[i]=(static_cast<float>(rand()%2000))/1000.0f-1.0f;
    subject[i]=(static_cast<float>(rand()%2000))/1000.0f-1.0f;
    object[i]=(static_cast<float>(rand()%2000))/1000.0f-1.0f;
  }
  normalizeWord(predicate);
  normalizeWord(object);
  normalizeWord(subject);
}

Request::Request(int invalid) :
subject(vector<float>(0)), object(vector<float>(0)), predicate(vector<float>(0))
{
    (void) invalid;
}

Request::Request(word subject_, word predicate_, word object_):
subject(subject_), object(object_), predicate(predicate_)
{
  normalizeWord(subject);
  normalizeWord(object);
  normalizeWord(predicate);
}

Request::Request(bool nulconstructor) :
subject(vector<float>(WORDSIZE,0)), object(vector<float>(WORDSIZE,0)), predicate(vector<float>(WORDSIZE,0))
{
    (void)nulconstructor;
}

Request::~Request(void)
{
}

bool Request::isValid() const
{
  return !predicate.empty();
}


float Request::getDistance2subject(Request r) const
{
  float sum=0.0f;
  float term;
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    term=(subject[i]-r.subject[i]);
    sum+=term*term;
  }
  return sqrt(sum/static_cast<float>(WORDSIZE));
}

float Request::getDistance2object(Request r) const
{
  float sum=0.0f;
  float term;
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    term=(object[i]-r.object[i]);
    sum+=term*term;
  }
  return sqrt(sum/static_cast<float>(WORDSIZE));
}

float Request::getDistance2predicate(Request r) const
{
  float sum=0.0f;
  float term;
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    term=(predicate[i]-r.predicate[i]);
    sum+=term*term;
  }
  return sqrt(sum/static_cast<float>(WORDSIZE));
}

ostream& Request::output(ostream& os)
{
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    os<<this->subject[i]<<" "<<this->predicate[i]<<" "<<this->object[i]<<" ";
  }
  return os;
}

istream& Request::input(istream& is)
{
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    is>>this->subject[i]>>this->predicate[i]>>this->object[i];
  }
  return is;
}

ostream& operator<<(ostream& os,Request& req)
{
  return req.output(os);
}

istream& operator>>(istream& is,Request& req)
{
  return req.input(is);
}

word& operator+=(word& w1,word w2)
{
  for(long unsigned int i=0;i<WORDSIZE;i++)
    w1[i]+=w2[i];
  return w1;
}

word operator+(word w1,word w2)
{
  word r;
  for(long unsigned int i=0;i<WORDSIZE;i++)
    r.push_back(w1[i]+w2[i]);
  return r;
}

word Request::getSubject(){return subject;}
word Request::getObject(){return object;}
word Request::getPredicate(){return predicate;}

word::iterator Request::getSubjectIterator(){return subject.begin();}
word::iterator Request::getObjectIterator(){return object.begin();}
word::iterator Request::getPredicateIterator(){return predicate.begin();}

Request Request::operator+(Request a)
{
  Request res;
  res.subject=this->subject+a.subject;
  res.object=this->object+a.object;
  res.predicate=this->predicate+a.predicate;
  return res;
}

void Request::operator+=(Request a)
{
  this->subject+=a.subject;
  this->object+=a.object;
  this->predicate+=a.predicate;
}

void Request::reset()
{
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    subject[i]=0;
    predicate[i]=0;
    object[i]=0;
  }
}



float Request::getTransformedDistancePredicate(Request& r, float limit) const
{
  float sum=0.0f;
  float term;
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    term=(subject[i]-r.subject[i]);
    sum+=term*term;
    if(sum>=limit)
      return numeric_limits<float>::infinity();
  }
return sum;
}

float Request::getTransformedDistanceObject(Request& r, float limit) const
{
  float sum=0.0f;
  float term;
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    term=(object[i]-r.object[i]);
    sum+=term*term;
    if(sum>=limit)
      return numeric_limits<float>::infinity();
  }
return sum;
}

float Request::getTransformedDistanceSubject(Request& r, float limit) const
{
  float sum=0.0f;
  float term;
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    term=(predicate[i]-r.predicate[i]);
    sum+=term*term;
    if(sum>=limit)
      return numeric_limits<float>::infinity();
  }
return sum;
}


void normalizeWord(word& w)
{
  float sum=0.0f;
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    sum+=w[i]*w[i];
  }
  sum/=WORDSIZE;
  sum=sqrt(sum);
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    w[i]/=sum;
  }
}