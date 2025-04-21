#ifndef CARIM_CarimRPCTypes
#define CARIM_CarimRPCTypes

enum CarimRPCTypes {
    START = -44999
}

enum CarimRPCTypesAutorun : CarimRPCTypes {
    AUTORUN
}

enum CarimRPCTypesChat : CarimRPCTypesAutorun {
    SEND
}

enum CarimRPCTypesParty : CarimRPCTypesChat {
    POSITIONS,
    MARKERS,
    REGISTER
}

#endif
