//
// Created by Sebastian Marshall on 2/28/23.
//

#ifndef PROJECT1_TOP_SONGS_H
#define PROJECT1_TOP_SONGS_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class Top_Songs {
private:
    std::string SongName, Artist, Genre,ID,Explicit;
    int Length,RatingPercent, Index;

public:
    Top_Songs(){
    }
    Top_Songs(int Index,
              std::string SongName,
              std::string Artist,
              std::string Genre,
              std::string ID,
              std::string Explicit,
              int Length,
              int RatingPercent){
        this->SongName = SongName;
        this->Artist = Artist;
        this->ID = ID;
        this->Genre = Genre;
        this->Explicit = Explicit;
        this->Index = Index;
        this->Length = Length;
        this->RatingPercent = RatingPercent;
    }
    //Getters
    std::string getSongName() const {
        return SongName;
    }
    std::string getArtist() const {
        return Artist;
    }
    std::string getGenre() const {
        return Genre;
    }
    std::string getID() const {
        return ID;
    }
    std::string getExplicit() const {
        return Explicit;
    }
    int getIndex() const {
        return Index;
    }
    int getLength() const {
        return Length;
    }
    int getRatingPercent() const {
        return RatingPercent;
    }

    //Setters
    void setSongName(std::string SongName) {
        this->SongName = SongName;
    }
    void setArtist(std::string Artist) {
        this->Artist = Artist;
    }
    void setGenre(std::string Genre) {
        this->Genre = Genre;
    }
    void setID(std::string ID) {
        this->ID = ID;
    }
    void setExplicit(std::string Explicit) {
        this->Explicit = Explicit;
    }
    void setIndex(int Index) {
        this->Index = Index;
    }
    void setLength(int Length) {
        this->Length = Length;
    }
    void setRatingPercent(int RatingPercent) {
        this->RatingPercent = RatingPercent;
    }

    friend std::ostream& operator << (std::ostream& outs, const Top_Songs& tObj) {
        outs << std::fixed
             << std::right
             << std::setprecision(4)
             << std::setw(6) << tObj.getIndex()
             << std::setw(75) << tObj.getSongName()
             << std::setw(40) << tObj.getArtist()
             << std::left
             << "  "
             << std::setw(150) << tObj.getGenre()
             << std::setw(20) << tObj.getExplicit()
             << std::right
             << std::setw(30) << tObj.getID()
             << std::setw(15) << tObj.getLength()
             << std::setw(10) << tObj.getRatingPercent();
        return outs;
    }

    friend bool operator < (const Top_Songs& lhs, const Top_Songs& rhs) {
        return lhs.getIndex() < rhs.getIndex();
    }

    friend bool operator > (const Top_Songs& lhs, const Top_Songs& rhs) {
        return lhs.getIndex() > rhs.getIndex();
    }

    friend bool operator <= (const Top_Songs& lhs, const Top_Songs& rhs) {
        return lhs.getIndex() <= rhs.getIndex();
    }

    friend bool operator >= (const Top_Songs& lhs, const Top_Songs& rhs) {
        return lhs.getIndex() >= rhs.getIndex();
    }

    friend bool operator == (const Top_Songs& lhs, const Top_Songs& rhs) {
        return lhs.getIndex() == rhs.getIndex();
    }

    friend bool operator != (const Top_Songs& lhs, const Top_Songs& rhs) {
        return lhs.getIndex() != rhs.getIndex();
    }

};

bool loadFromFile(std::string fn, std::vector<Top_Songs>& objs) {
    std::ifstream fin;
    fin.open(fn);

    if (!fin) {
        //File won't open
        return false;
    }
    //Removing Header
    std::string header = "";
    getline(fin, header);

    // Read in data while the file is still good
    // ,and we haven't yet reached the end of file (EOF).
    int counter = 1;
    while (fin && fin.peek() != EOF) {
        // We initialize variables to sentinel values --
        // values we *know* will not appear in our data.
        // If any object fields have one of these values, we
        // *know* it was incorrectly set.

        std::string SongName = "INVALID";
        std::string Artist = "INVALID";
        std::string Genre = "INVALID";
        std::string ID = "INVALID";
        std::string Explicit = "INVALID";
        int Index = -1;
        int Length = -1;
        int PercentRating = -1;

        char comma = ','; // This will come in handy.
        char quote = '"';
        string junk;


        // Using the >> (extraction) operator ...
        fin >> Index;  // Expects an int; reads an int.
        if (Index != counter) {
            std::cout << Index << " != " << counter << std::endl;
            return false;
        }
        fin >> comma;
        // These read a string; comma is delimiter.
        getline(fin, SongName, comma);
        getline(fin, Artist, comma);
        fin >> quote;
        getline(fin, Genre, quote);
        fin >> comma;

        getline(fin, ID, ',');
        fin >> Length;
        fin >> comma;
        getline(fin, Explicit, ',');
        // We can't use the technique we used above. Here we check
        // to make sure that the next character isn't a newline or
        // carriage return. This will happen if koi_kepmag is missing
        // in the source data file (there's one annoying record).
        //if (fin.peek() != '\r' && fin.peek() != '\n') {
        fin >> PercentRating;
        //}
        getline(fin,junk);
        Top_Songs Songs(Index,SongName,Artist, Genre, ID,
                        Explicit, Length, PercentRating);
        objs.push_back(Songs);
        counter += 1;
    }
    fin.close();
    return true;
};
void AverageRating(std::vector<Top_Songs>& objs) {
    int totalShort = 0;
    int totalLong = 0;
    int NumSongs = 0;
    int NumSongsShort = 0;
    int NumSongsLong = 0;

    for (Top_Songs& top : objs) {
        int rating = top.getRatingPercent();
        int length = top.getLength();
        if (length<200000){
            totalShort += rating;
            NumSongsShort +=1;
        }else{
            totalLong += rating;
            NumSongsLong +=1;
        }
        NumSongs +=1;

    }

    int AvgShort = totalShort/NumSongsShort;
    int AvgLong = totalLong/NumSongsLong;
    int Avg = (AvgLong+AvgShort)/2;

    std::cout << std::endl;
    std::cout << "Average Rating Long vs Short Songs" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Total Number of Short songs" << std::right << std::setw(20)
              << NumSongsShort << std::endl;
    std::cout << "Total Number of Long songs" << std::right << std::setw(20)
              << NumSongsLong<< std::endl;
    std::cout << "Total Number of songs" << std::right << std::setw(20)
              << NumSongs << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Average Rating for songs less than 3 minutes and 20 seconds" << std::right << std::setw(15)
              << AvgShort << std::endl;
    std::cout << "Average Rating for songs Greater than 3 minutes and 20 seconds" << std::right << std::setw(16)
              << AvgLong << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Average Rating Overall" << std::right << std::setw(20)
              << Avg << std::endl;
    std::cout << "==========================" << std::endl;
}

void showSongStats(std::vector<Top_Songs>& objs) {
    int explicit_songs = 0;
    int clean = 0;
    int other = 0;
    int total;

    for (Top_Songs& top : objs) {
        std::string Exp = top.getExplicit();
        if (Exp.compare("TRUE") == 0) {
            explicit_songs += 1;
        } else if (Exp.compare("FALSE") == 0) {
            clean += 1;
        } else {
            // This should never happen! If this is anything other than
            // 0 we know something unexpected has occurred, e.g., some
            // value for KOI disposition not included in the above.
            other += 1;
        }
    }

    total = explicit_songs + clean + other;

    std::cout << std::endl;
    std::cout << "Explicit song statistics" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Explicit Songs" << std::right << std::setw(15)
              << explicit_songs << std::endl;
    std::cout << "Clean Songs" << std::right << std::setw(16)
              << clean << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Total" << std::right << std::setw(20)
              << total << std::endl;
    std::cout << "==========================" << std::endl;
}

/**
 * This verifies that all fields that should be set are set with
 * good values. Some fields may have missing values, e.g. keplerName,
 * koiScore and koiKepmag. In the case of keplerName, we just set it
 * to empty string. koiScore and koiKepmag are doubles so if a value
 * is missing in the source data, these will be set to a sentinel
 * value of -1. If we ever do calculations on these fields we know
 * then to exclude any values of -1 from our calculations.
 */
void verifyAllFieldsSet(std::vector<Top_Songs>& objs) {
    int i = 0;
    for (Top_Songs& top : objs) {
        // Row ID should always = i + 1
        if (top.getIndex() != i + 1) {
            std::cout << "Bad value for index Record"
                      << i << std::endl;
        }
        if (top.getLength() == -1) {
            std::cout << "Bad value for length at record "
                      << i << std::endl;
        }
        std::string name = top.getSongName();
        if (name.compare("INVALID") == 0) {
            std::cout << "Bad value for song name at record "
                      << i << std::endl;
        }
        std::string artist = top.getArtist();
        if (artist.compare("INVALID") == 0) {
            std::cout << "Bad value for artist name at record "
                      << i << std::endl;
        }
        std::string genre = top.getGenre();
        if (genre.compare("INVALID") == 0) {
            std::cout << "Bad value for genre at record "
                      << i << std::endl;
        }
        std::string id = top.getID();
        if (id.compare("INVALID") == 0) {
            std::cout << "Bad value for genre at record "
                      << i << std::endl;
        }
        std::string expl = top.getExplicit();
        if (expl.compare("INVALID") == 0) {
            std::cout << "Bad value for explicit at record "
                      << i << std::endl;
        }
        i += 1;
    }
}


#endif //PROJECT1_TOP_SONGS_H

