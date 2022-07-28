#include "pch.h"
#include <EventAPI.h>
#include <LoggerAPI.h>
#include <MC/Level.hpp>
#include <MC/BlockInstance.hpp>
#include <MC/Block.hpp>
#include <MC/BlockSource.hpp>
#include <MC/Actor.hpp>
#include <MC/Player.hpp>
#include <MC/ItemStack.hpp>
#include "Version.h"
#include <LLAPI.h>
#include <ServerAPI.h>
#include "ModUtils.h"

#include <MC/BedrockBlocks.hpp>
#include <MC/PerlinNoise.hpp>
#include <MC/PerlinSimplexNoise.hpp>
Logger logger(PLUGIN_NAME);
#define ENABLE_VIRTUAL_FAKESYMBOL_OVERWORLDGENERATORMULTINOISE
auto ne = PerlinSimplexNoise::PerlinSimplexNoise(11,114514);

inline void CheckProtocolVersion() {
#ifdef TARGET_BDS_PROTOCOL_VERSION
    auto currentProtocol = LL::getServerProtocolVersion();
    if (TARGET_BDS_PROTOCOL_VERSION != currentProtocol)
    {
        logger.warn("Protocol version not match, target version: {}, current version: {}.",
            TARGET_BDS_PROTOCOL_VERSION, currentProtocol);
        logger.warn("This will most likely crash the server, please use the Plugin that matches the BDS version!");
    }
#endif // TARGET_BDS_PROTOCOL_VERSION
}

void PluginInit()
{
    CheckProtocolVersion();
    logger.info << "Hello,world!" << logger.endl;
}

#include <MC/OverworldGenerator.hpp>
#include<MC/SurfaceLevelCache.hpp>
#include <MC/LevelChunk.hpp>
#include <MC/ChunkBlockPos.hpp>
#include <MC/HeightmapWrapper.hpp>
#include <MC/BlockVolume.hpp>
#include <MC/ServerCommandOrigin.hpp>
#include <MC/TeleportComponent.hpp>
#include <MC/ExhaustionComponent.hpp>
#include <MC/OverworldGeneratorMultinoise.hpp>
//THook(void, "?_prepareHeights@OverworldGeneratorMultinoise@@EEAAXAEAVBlockVolume@@AEBVChunkPos@@AEBVWorldGenCache@@PEAVAquifer@@$$QEAV?$function@$$A6AXAEBVBlockPos@@AEBVBlock@@H@Z@std@@_NPEAV?$vector@FV?$allocator@F@std@@@7@H@Z"
//	, ServerCommandOrigin* a1,
//	BlockVolume* a2,
//	unsigned __int64* a3,
//	int a4,
//	TeleportComponent* a5,
//	__int64 a6,
//	char a7,
//	void** a8) {
//	OreVeinifier* v17; // rax
//	//Block* VeinBlockOrFallback = (Block*)OreVeinifier::getVeinBlockOrFallback(v120, v132, Block);;
//	if (VeinBlockOrFallback == BedrockBlocks::mAir)
//	{
//		VeinBlockOrFallback = Block::create("minecraft:stone", 0);
//	}
//	return original(a1, a2, a3, a4, a5, a6, a7, a8);
//}

//#include <MC/OreVeinifierNoises.hpp>
THook(void*, "?getVeinBlockOrFallback@OreVeinifier@@QEBAPEBVBlock@@VVec3@@PEBV2@@Z",
    void** a1,
    float* a2,
    void* a3) {
    auto ori = original(a1, a2, a3);
    //logger.info << ((Block*)ori)->getTypeName() << logger.endl;
    return (void*)(Block::create("minecraft:stone", 0));
    if ((Block*)ori == BedrockBlocks::mAir)
    {
        return (void*)(Block::create("minecraft:stone", 0));
    }
    return ori;
}

#include <MC/Dimension.hpp>
#include<MC/WorldGenerator.hpp>
THook(void, "?buildSurfaces@OverworldGenerator@@QEAAXAEAUThreadData@1@AEAVBlockVolume@@AEAVLevelChunk@@AEBVChunkPos@@AEBVSurfaceLevelCache@@@Z",
    OverworldGenerator* _this,
    OverworldGenerator::ThreadData* a2,
    BlockVolume* a3,
    LevelChunk* a4,
    const ChunkPos* a5,
    const SurfaceLevelCache* a6) {
    //logger.info <<  a5->x << " " << a5->z << logger.endl;
    return;
}
//
//#include <memory>
//THook(void, "?loadChunk@OverworldGenerator@@UEAAXAEAVLevelChunk@@_N@Z",
//    OverworldGenerator* _this, LevelChunk* a2) {
//    //BedrockBlocks::mAir = Block::create("minecraft:stone", 0);
//    return original(_this,a2);
//}

//THook(void, "?setPreWorldGenHeightMap@LevelChunk@@QEAAXV?$unique_ptr@V?$vector@FV?$allocator@F@std@@@std@@U?$default_delete@V?$vector@FV?$allocator@F@std@@@std@@@2@@std@@@Z",
//    __int64 a1, std::unique_ptr<std::vector<short>>& a2) {
//    if (a2)
//    {
//        (*a2) = { 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256 };
//        logger.info << a2.get()->size() << 
//            fmt::format(" {0} {1} {2} {3} {4}", 
//            (*(std::vector<short>*)(a2.get()))[0],
//            (*(std::vector<short>*)(a2.get()))[1], 
//            (*(std::vector<short>*)(a2.get()))[2], 
//            (*(std::vector<short>*)(a2.get()))[3], 
//            (*(std::vector<short>*)(a2.get()))[4]) << logger.endl;
//    }
//    return original(a1,a2);
//}

//THook(float, "?getValue@PerlinSimplexNoise@@QEBAMMM@Z",
//    PerlinSimplexNoise* _this, float a2, float a3) {
//    //logger.info << original(_this, a2, a3) << logger.endl;
//    return 114514;
//}

//THook(long long, "?make@Noises@OverworldGeneratorMultinoise@@SA?AU12@AEBVXoroshiroPositionalRandomFactory@@@Z",
//    __int64 a1, __int64 a2) {
//
//}
// 
//#include <MC/TargetPoint.hpp>
//#include <MC/OverworldGeneratorMultinoise.hpp>
//THook(PerlinSimplexNoise, "?getSurfaceNoise@OverworldGeneratorMultinoise@@MEAAAEBVPerlinSimplexNoise@@XZ",
//    OverworldGeneratorMultinoise* _this) {
//    auto ori = original(_this);
//    //logger.info << (void*)ori << logger.endl;
//    return ne;
//}

//TInstanceHook(PerlinSimplexNoise*, "??0PerlinSimplexNoise@@QEAA@IH@Z",
//    PerlinSimplexNoise,
//    unsigned int a2,
//    int a3) {
//    if (a2&&a3)
//    {
//        logger.info << a2 << " " << a3 << logger.endl;
//    }
//    return original(this, 0, 0);
//}

#include <MC/BedrockBlocks.hpp>
#include <MC/SubChunk.hpp>
THook(long long, "??0BlockVolume@@QEAA@V?$buffer_span_mut@PEBVBlock@@@@HHHAEBVBlock@@H@Z",
    __int64 a1,
    void* a2,
    int a3,
    int a4,
    int a5,
    unsigned __int64 a6,
    int a7) {
    if (a6)
    {
        auto bl = Block::create("minecraft:stone", 0);
        //logger.info << a4 << logger.endl;
        return original(a1, a2, a3, 320, a5, (unsigned __int64)bl, 320);
    }
    return original(a1, a2, a3, a4, a5, a6, a7);
}

//THook(void, "?setBlockVolume@LevelChunk@@QEAAXAEBVBlockVolume@@I@Z",
//    LevelChunk* _this, const BlockVolume* a2, __int16 a3) {
//     __int16 HighestNonAirBlock; // ax
//    __int16 v7; // ax
//    __int16 v8; // di
//    __int64 v9; // rbx
//    __int16 v10; // si
//    __int64 v11; // rax
//    __int64 v12; // rdi
//    __int64 v13; // rbx
//    *((unsigned __int64*)a2 + 7) = 320;
//    HighestNonAirBlock = a2->findHighestNonAirBlock();
//    if (HighestNonAirBlock != *((unsigned __int64*)a2 + 7))
//    {
//        logger.info << HighestNonAirBlock << logger.endl;
//        v7 = HighestNonAirBlock - *((unsigned __int16*)a2 + 14) + a3;
//        v8 = a3 >> 4;
//        v9 = (v7 >> 4) + 1i64;
//        v10 = 0;
//        v11 = v8;
//        if (v8 != v9)
//        {
//            v12 = 96i64 * v8;
//            v13 = v9 - v11;
//            do
//            {
//                ((SubChunk*)(v12 + *((unsigned __int64*)_this + 39)))->setFromBlockVolume(*a2, v10);
//                v10 += 16;
//                v12 += 96i64;
//                --v13;
//            } while (v13);
//        }
//    }
//    return original(_this, a2, a3);
//}
//
//THook(__int16, "?findHighestNonAirBlock@BlockVolume@@QEBAFXZ",
//    BlockVolume* _this) {
//    return 320;
//}
//
//#include <MC/PerlinSimplexNoise.hpp>
//#include <MC/OverworldGeneratorMultinoise.hpp>
//THook(PerlinSimplexNoise*, "?getSurfaceNoise@OverworldGeneratorMultinoise@@MEAAAEBVPerlinSimplexNoise@@XZ",
//    OverworldGeneratorMultinoise* _this) {
//    auto ori = original(_this);
//
//}