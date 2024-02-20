#ifndef IBF_HPP
#define IBF_HPP

#include "ibf-indexer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>



static const int IBF_DEFAULT_SIZE = 50;
static const int IBF_DEFAULT_QTD_HASH_FUNCTIONS = 3;
//static const IndexerType IBF_DEFAULT_INDEXER_TYPE = IndexerType::vector;
static const IndexerType IBF_DEFAULT_INDEXER_TYPE = IndexerType::map;

// Ref: https://github.com/daankolthof/bloomfilter/blob/master/bloomfilter/bloomfilter.h

template <typename T> std::string join2(const T &v, const std::string &delim) {
  std::ostringstream s;
  for (const auto &i : v) {
    if (&i != &v[0]) {
      s << delim;
    }
    s << i;
  }
  return s.str();
}

class InvertibleBloomFilter {
public:

    InvertibleBloomFilter(int size, int hashFunctions){
        	if (IBF_DEFAULT_INDEXER_TYPE == IndexerType::vector){
        		m_indexer = new VectorIndexer(size, hashFunctions);
        	}else{
    			m_indexer = new MapIndexer(size, hashFunctions);
        	}
        }

    InvertibleBloomFilter(int size, int hashFunctions, int count, std::vector<size_t> numbers){
        	if (IBF_DEFAULT_INDEXER_TYPE == IndexerType::vector){
        		m_indexer = new VectorIndexer(size, hashFunctions, count, numbers);
        	}else{
    			m_indexer = new MapIndexer(size, hashFunctions, count, numbers);
        	}
        }

    void insert(const std::string& element) {
    	m_indexer->insert(element);
    }

    void remove(const std::string& element) {
       m_indexer->remove(element);
    }

    bool contains(const std::string& element) const {
    	return m_indexer->contains(element);
    }
    
    bool operator==(InvertibleBloomFilter const &obj) {
    	 if (IBF_DEFAULT_INDEXER_TYPE == IndexerType::vector)
    	 	return *dynamic_cast<VectorIndexer*>(this->m_indexer) == *dynamic_cast<VectorIndexer*>(obj.m_indexer); 
	     return *dynamic_cast<MapIndexer*>(this->m_indexer) == *dynamic_cast<MapIndexer*>(obj.m_indexer);
  	}

    bool is_empty() const {
        return get_count() == 0;
    }

    int get_count() const {
        return m_indexer->getCount();
    }

    InvertibleBloomFilter *copy(){
    	return new InvertibleBloomFilter(this->m_indexer->getSize(), 
    		this->m_indexer->getHashFunctions(), 
    		this->m_indexer->getCount(), 
    		this->m_indexer->getNumbers());
    }

    std::vector<size_t> getNumbers() const{
    	return m_indexer->getNumbers();
    }

protected:
	AbstractIndexer *m_indexer;

};

#endif // IBF_HPP
