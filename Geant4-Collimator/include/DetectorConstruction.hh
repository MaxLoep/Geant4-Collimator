#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class DetectorMessenger;


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
   ~DetectorConstruction();

  public:

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    void SetOutputFolder (std::string);
    void SetAbsorMaterial (G4String);

    void change_a   (G4double);
    void change_b   (G4double);
    void change_c   (G4double);
    void change_d   (G4double);
    void change_e   (G4double);
    void change_f   (G4double);

  public:  

   G4double GetAbsorThickness()    {return boxX;};
   G4double GetAbsorSizeYZ()       {return boxX;};
   G4Material* GetAbsorMaterial()  {return boxMaterial;};

   G4double GetWorldSizeX()   {return boxX;};
   G4double GetWorldSizeYZ()  {return boxX;};

   void PrintParameters();

  private:

  // Define Variables for Materials and geometries you want to change per macro-file HERE:

  

  //world size 
  G4double world_sizeXYZ;

  // for the box
   G4double           boxX;
   G4double           boxY;
   G4double           boxZ;

// dummy variables
   G4double           a;
   G4double           b;
   G4double           c;
   G4double           d;
   G4double           e;
   G4double           f;

   G4double           TargetDia;
   G4double           TargetLen;
   G4double           TubeDia;
   G4double           TubeLen;
   G4double           colli_angle;
   G4double           x;
   G4double           Entrance_Radius;
   G4double           Inner_Radius;
   G4double           Exit_Radius;

   G4Material*        fAbsorMaterial;
   G4LogicalVolume*   fLAbsor;

   G4Material*        world_mat;
   G4Material*        boxMaterial;
   G4Material*        dummyMat; 

   G4Material*        Vacuum; 

   G4Material*        TargetMat; 
   G4Material*        DetectorMat; 
   G4Material*        TubeMat; 
   G4Material*        Copper;
   G4Material*        Tungsten;
   G4Material*        Iron;
   G4Material*        Nickel;
   G4Material*        Densimet180;  

   G4Material*        Hydrogen;
   G4Material*        Carbon;
   G4Material*        Boron;
   G4Material*        BoratedPE;               

   DetectorMessenger* fDetectorMessenger;

  private:

   void               DefineMaterials();
   G4VPhysicalVolume* ConstructVolumes(); 

  protected:
    G4LogicalVolume*  fScoringVolume;    
};


#endif
