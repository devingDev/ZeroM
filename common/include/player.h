#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "helperfunctions.h"

typedef struct Player Player, *PPlayer;
typedef struct Player_vtbl Player_vtbl, *PPlayer_vtbl;
typedef struct Player2 Player2, *PPlayer2;

struct Player {
    Player_vtbl *__vftable;
    char pad00[0xC4]; 
    double posx1; //0xC8
    double posy1; //0xD0
    double posz1; //0xD8
    float angleA; //0xE0
    float angleB; //0xE4
    char pad01[0x18]; //0xE8
    double posx2; //0x100
    double posy2; //0x108
    double posz2; //0x110
    double posx3; //0x118
    double posy3; //0x120
    double posz3; //0x128
    char pad02[0x18]; //0x130
    float angle1; //0x148
    float angle2; //0x14C
    float angle3; //0x150
    float angle4; //0x154
    float angle5; //0x158
    float angle6; //0x15C
    char pad03[0x60]; //0x160
    double posx4; //0x1C0
    double posy4; //0x1C8
    double posz4; //0x1D0
    char pad04[0x6F0]; //0x1D8
    double posx5; //0x8C8
    double posy5; //0x8D0
    double posz5; //0x8D8

    //unsigned char extraData[0xA8C];
}; // i think this was around 0xA90 bytes?
struct Player2 {
    unsigned char extraData[0xA90];
    //struct Player_vtbl *__vftable;
    //unsigned char extraData[0xA8C];
};

typedef struct {
    double x;
    double y;
    double z;
} Vec3;

#define undefRet int
typedef undefRet (*FunctionType)(Player* player);
#define undefPlayerFun FunctionType

struct Player_vtbl { /* vtable of Player */
    char pad00[0x30]; // 0x0
    undefPlayerFun GetType; //fjDerivedCtorCalls__12LivingEntityFv
    undefPlayerFun fjDerivedCtorCalls__12LivingEntityFv; //fjDerivedCtorCalls__12LivingEntityFv
    undefPlayerFun kill__12LivingEntityFv; //kill__12LivingEntityFv
    undefPlayerFun defineSynchedData__6PlayerFv; //defineSynchedData__6PlayerFv
    undefPlayerFun resetPos__6PlayerFv; //resetPos__6PlayerFv
    undefPlayerFun remove__6PlayerFv; //remove__6PlayerFv
    undefPlayerFun setDropContainerContent__6EntityFb; //setDropContainerContent__6EntityFb
    undefPlayerFun setSize__6EntityFfT1; //setSize__6EntityFfT1
    undefPlayerFun setPos__6EntityFdN21; //setPos__6EntityFdN21
    undefPlayerFun tick__6PlayerFv; //tick__6PlayerFv
    undefPlayerFun baseTick__12LivingEntityFv; //baseTick__12LivingEntityFv
    undefPlayerFun processDimensionDelay__6EntityFv; //processDimensionDelay__6EntityFv
    undefPlayerFun getPortalWaitTime__6PlayerFv; //getPortalWaitTime__6PlayerFv
    undefPlayerFun setSecondsOnFire__6EntityFi; //setSecondsOnFire__6EntityFi
    undefPlayerFun clearFire__6EntityFv; //clearFire__6EntityFv
    undefPlayerFun outOfWorld__12LivingEntityFv; //outOfWorld__12LivingEntityFv
    undefPlayerFun move__6EntityF9MoverTypedN22b; //move__6EntityF9MoverTypedN22b
    undefPlayerFun updateDeltaAfterMove__6EntityFP5BlockdN22RdN25; //updateDeltaAfterMove__6EntityFP5BlockdN22RdN25
    undefPlayerFun setLocationFromBoundingbox__6EntityFv; //setLocationFromBoundingbox__6EntityFv
    undefPlayerFun getSwimSound__6PlayerFv; //getSwimSound__6PlayerFv
    undefPlayerFun getSwimSplashSound__6PlayerFv; //getSwimSplashSound__6PlayerFv
    undefPlayerFun getHeavySplashSound__6PlayerFv; //getHeavySplashSound__6PlayerFv
    undefPlayerFun checkInsideBlocks__6EntityFv; //checkInsideBlocks__6EntityFv
    undefPlayerFun onInsideBlock__6EntityFPC10BlockState; //onInsideBlock__6EntityFPC10BlockState
    undefPlayerFun playStepSound__6EntityFRC8BlockPosP5Block; //playStepSound__6EntityFRC8BlockPosP5Block
    undefPlayerFun playUnderwaterSound__6EntityFRC8BlockPosP5Block; //playUnderwaterSound__6EntityFRC8BlockPosP5Block
    undefPlayerFun playFlySound__6EntityFf; //playFlySound__6EntityFf
    undefPlayerFun makeFlySound__6EntityFv; //makeFlySound__6EntityFv
    undefPlayerFun playSound__6PlayerFPC10SoundEventfT2; //playSound__6PlayerFPC10SoundEventfT2
    undefPlayerFun isSilent__6EntityFv; //isSilent__6EntityFv
    undefPlayerFun setSilent__6EntityFb; //setSilent__6EntityFb
    undefPlayerFun isNoGravity__6EntityFv; //isNoGravity__6EntityFv
    undefPlayerFun setNoGravity__6EntityFb; //setNoGravity__6EntityFb
    undefPlayerFun isMoving__6EntityFv; //isMoving__6EntityFv
    undefPlayerFun setMoving__6EntityFb; //setMoving__6EntityFb
    undefPlayerFun makeStepSound__6PlayerFv; //makeStepSound__6PlayerFv
    undefPlayerFun checkFallDamage__12LivingEntityFdbP5BlockRC8BlockPos; //checkFallDamage__12LivingEntityFdbP5BlockRC8BlockPos
    undefPlayerFun getCollideBox__6EntityFv; //getCollideBox__6EntityFv
    undefPlayerFun burn__6EntityFi; //burn__6EntityFi
    undefPlayerFun causeFallDamage__6PlayerFfT1; //causeFallDamage__6PlayerFfT1
    undefPlayerFun isInWater__6EntityFv; //isInWater__6EntityFv
    undefPlayerFun headInWater__6EntityFv; //headInWater__6EntityFv
    undefPlayerFun isOverWater__6EntityFv; //isOverWater__6EntityFv
    undefPlayerFun updateInWaterState__6EntityFv; //updateInWaterState__6EntityFv
    undefPlayerFun doWaterSplashEffect__6PlayerFv; //doWaterSplashEffect__6PlayerFv
    undefPlayerFun updateSprintingState;
    undefPlayerFun doSprintParticleEffect; // 0xE8
    
    undefRet (*isUnderLiquid)(Player* player, int a1); // 0xEC
    undefRet (*isInLiquid)(Player* player, int a1, double *a2); // 0xF0
    undefRet (*getLightColor)(Player* player); // 0xF4
    double (*getBrightness) (Player* player); // 0xF8
    undefRet (*setLevel) (Player* player, int a1); // 0xFC


    int (*moveTo)(Player* player, double x, double y, double z, double angle1, double angle2); // 0x100

    undefPlayerFun playerTouch__6EntityFQ2_5boost25shared_ptr__tm__8_6Player; // 0x104
    undefPlayerFun push__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun push__6EntityFdN21;
    undefPlayerFun markHurt__12LivingEntityFv;
    undefPlayerFun hurt__6PlayerFPC12DamageSourcef;
    undefPlayerFun getViewVector__12LivingEntityFf;
    undefPlayerFun isPickable__6PlayerFv;
    undefPlayerFun isPushable__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun awardKillScore__6EntityFQ2_5boost25shared_ptr__tm__8_6EntityiPC12DamageSource;
    undefPlayerFun shouldRender__6EntityFdN21;
    undefPlayerFun shouldRender__6EntityFd;
    undefPlayerFun shouldRenderAtSqrDistance__6PlayerFd;
    undefPlayerFun save__6EntityFP11CompoundTag;
    undefPlayerFun load__6EntityFP11CompoundTag;
    undefPlayerFun shouldTick__6PlayerFv;
    undefPlayerFun repositionEntityAfterLoad__6EntityFv;
    undefPlayerFun readAdditionalSaveData__6PlayerFP11CompoundTag;
    undefPlayerFun addAdditonalSaveData__6PlayerFP11CompoundTag;
    undefPlayerFun readAdditionContructionTag__6EntityFP11CompoundTag_9;
    undefPlayerFun getAdditionContructionTag__6EntityFv;
    undefPlayerFun spawnAtLocation__6EntityFP4Itemi;
    undefPlayerFun spawnAtLocation__6EntityFP4Itemif;
    undefPlayerFun spawnAtLocation__6EntityF35not_null_ptr__tm__15_12ItemInstancef;
    undefPlayerFun isAlive__12LivingEntityFv;
    undefPlayerFun isInWall__6PlayerFv;
    undefPlayerFun interact__6EntityFRCQ2_5boost25shared_ptr__tm__8_6PlayerQ2_15InteractionHand16EInteractionHand;
    undefPlayerFun getCollideAgainstBox__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun rideTick__6PlayerFv;
    undefPlayerFun positionRider__6EntityFRCQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun onPassengerTurned__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun getRidingHeight__6PlayerFv;
    undefPlayerFun getRideHeight__6EntityFv;
    undefPlayerFun showVehicleHealth__6EntityFv;
    undefPlayerFun startRiding__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun startRiding__6EntityFQ2_5boost25shared_ptr__tm__8_6Entityb;
    undefPlayerFun GetInteractTooltip__6EntityFRC23EntityTooltipDataHolder;
    undefPlayerFun GetHitTooltip__6EntityFRC23EntityTooltipDataHolder;
    undefPlayerFun HideUseTooltips__6EntityFv;
    undefPlayerFun canRide__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun ejectPassengers__6EntityFv;
    undefPlayerFun stopRiding__6PlayerFv;
    undefPlayerFun stopRidingBeforeTeleport__6EntityFv;
    undefPlayerFun addPassenger__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun removePassenger__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun canAddPassenger__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun lerpTo__12LivingEntityFdN21fT4ib;
    undefPlayerFun getPickRadius__6EntityFv;
    undefPlayerFun getLookAngle__6EntityFv;
    undefPlayerFun getRotationVector__6EntityFv; // 0x1C4

    Vec3* (*getForward)(Player* player); // 0x1C8

    undefPlayerFun handleInsidePortal__6EntityFRC8BlockPos; // 0x1CC
    undefPlayerFun getDimensionChangingDelay__6PlayerFv;
    undefPlayerFun lerpMotion__6EntityFdN21;
    undefPlayerFun handleEntityEvent__6PlayerFUci;
    undefPlayerFun animateHurt__12LivingEntityFv;
    undefPlayerFun getHandSlots__6PlayerFv;
    undefPlayerFun getArmorSlots__6PlayerFv;
    undefPlayerFun getAllSlots__6EntityFv;
    undefPlayerFun setItemSlot__6PlayerFPC13EquipmentSlot35not_null_ptr__tm__15_12ItemInstance;
    undefPlayerFun isOnFire__6EntityFv;
    undefPlayerFun isPassenger__6EntityFv;
    undefPlayerFun isVehicle__6EntityFv;
    undefPlayerFun isSneaking__6EntityFv;
    undefPlayerFun setSneaking__6EntityFb;
    undefPlayerFun isIdle__6EntityFv;
    undefPlayerFun setIsIdle__6EntityFb;
    undefPlayerFun isSprinting__6EntityFv;
    undefPlayerFun setSprinting__12LivingEntityFb;
    undefPlayerFun isSwimming__6EntityFv;
    undefPlayerFun isSwimmer__6EntityFv;
    undefPlayerFun startSwimming__6EntityFv;
    undefPlayerFun stopSwimming__6EntityFv;
    undefPlayerFun setSwimmer__6EntityFb;
    undefPlayerFun setDamageNearbyMobs__6EntityFb;
    undefPlayerFun getDamageNearbyMobs__6EntityFv;
    undefPlayerFun isGlowing__6EntityFv;
    undefPlayerFun setGlowing__6EntityFb;
    undefPlayerFun isInvisible__6EntityFv;
    undefPlayerFun isInvisibleTo__6PlayerFQ2_5boost25shared_ptr__tm__8_6Player;
    undefPlayerFun getTeam__6PlayerFv;
    undefPlayerFun isAlliedTo__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun isAlliedTo__6EntityFP4Team;
    undefPlayerFun setInvisible__6PlayerFb;
    undefPlayerFun ShouldRenderShadow__6PlayerFv;
    undefPlayerFun canFly__6EntityFv;
    undefPlayerFun getAttachPos__6PlayerFQ2_6Entity15EEntityLocationf;
    undefPlayerFun getMaxAirSupply__6EntityFv;
    undefPlayerFun setAirSupply__6EntityFi;
    undefPlayerFun thunderHit__6EntityFPC13LightningBolt;
    undefPlayerFun onAboveBubbleCol__6EntityFb;
    undefPlayerFun killed__6PlayerFQ2_5boost33shared_ptr__tm__15_12LivingEntity;
    undefPlayerFun checkInBlock__6EntityFdN21;
    undefPlayerFun spawnEatParticles__12LivingEntityFRC12ItemInstancei;
    undefPlayerFun makeStuckInWeb__6PlayerFv;
    undefPlayerFun getName__6PlayerFv;
    undefPlayerFun isInvulnerableTo__6EntityFPC12DamageSource;
    undefPlayerFun isInvulnerable__6EntityFv;
    undefPlayerFun setInvulnerable__6EntityFb;
    undefPlayerFun getSubEntities__6EntityFv;
    undefPlayerFun is__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun getYHeadRot__12LivingEntityFv;
    undefPlayerFun setYHeadRot__12LivingEntityFf;
    undefPlayerFun setYBodyRot__12LivingEntityFf;
    undefPlayerFun isAttackable__6EntityFv;
    undefPlayerFun skipAttackInteraction__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun copyPosition__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun changeDimension__6EntityFi;
    undefPlayerFun canChangeDimensions__6EntityFv;
    undefPlayerFun getBlockExplosionResistance__6EntityFP9ExplosionP5LevelRC8BlockPos;
    undefPlayerFun shouldBlockExplode__6EntityFP9ExplosionP5LevelRC8BlockPosf;
    undefPlayerFun getMaxFallDistance__6EntityFv;
    undefPlayerFun getPortalEntranceBlock__6EntityFv;
    undefPlayerFun getPortalEntranceOffset__6EntityFv;
    undefPlayerFun getPortalEntranceForwards__6EntityFv;
    undefPlayerFun isIgnoringBlockTriggers__6EntityFv;
    undefPlayerFun displayFireAnimation__6EntityFv;
    undefPlayerFun setUUID__6EntityFRCQ2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_w;
    undefPlayerFun getUUID__6EntityFv;
    undefPlayerFun getStringUUID__6EntityFv;
    undefPlayerFun isPushedByWater__6PlayerFv;
    undefPlayerFun getViewScale__6EntityFv;
    undefPlayerFun setViewScale__6EntityFd;
    undefPlayerFun getDisplayOrNetworkNam;
    
    // one of these functions is missing on psvita! i left them here as comments, because on wiiu its different
    // undefPlayerFun getDisplayName__6PlayerFv;
    // undefPlayerFun getNetworkName__6PlayerFv; 
    undefPlayerFun setCustomName__6EntityFRCQ2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wT1b;
    undefPlayerFun getCustomName__6EntityFv;
    undefPlayerFun hasCustomName__6EntityFv;
    undefPlayerFun setCustomNameVisible__6EntityFb;
    undefPlayerFun isCustomNameVisible__6EntityFv;
    
    int (*teleportTo)(Player* player, double x, double y, double z); // 0x304

    undefPlayerFun shouldShowName__6PlayerFv;
    undefPlayerFun onSyncedDataUpdated__6PlayerFPC23EntityDataAccessor_Base;
    undefPlayerFun getDirection__6EntityFv;
    undefPlayerFun getMotionDirection__6EntityFv;
    undefPlayerFun broadcastToPlayer__6EntityFQ2_5boost33shared_ptr__tm__15_12ServerPlayer;
    undefPlayerFun getBoundingBoxForCulling__6EntityFv;
    undefPlayerFun setBoundingBox__12LivingEntityFP4AABB;
    undefPlayerFun getEyeHeight__6PlayerFv;
    undefPlayerFun setSlot__6PlayerFiRC35not_null_ptr__tm__15_12ItemInstance;
    undefPlayerFun sendMessage__6PlayerFQ2_21ClientboundChatPacket18EChatPacketMessagePiUiPQ2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wT3;
    undefPlayerFun hasPermission__6EntityF12EGameCommand;
    undefPlayerFun getCommandSenderBlockPosition__6EntityFv;
    undefPlayerFun getCommandSenderWorldPosition__6EntityFv;
    undefPlayerFun getCommandSenderWorld__6EntityFv;
    undefPlayerFun getCommandSenderEntity__6EntityFv;
    undefPlayerFun isSendMessageEnabled__6PlayerFv;
    undefPlayerFun setCommandStats__6EntityFQ2_12CommandStats15CommandStatTypei;
    undefPlayerFun getServer__6EntityFv;
    undefPlayerFun interactAt__6EntityFRCQ2_5boost25shared_ptr__tm__8_6PlayerP4Vec3Q2_15InteractionHand16EInteractionHand;
    undefPlayerFun ignoreExplosion__6EntityFv;
    undefPlayerFun startSeenByPlayer__6EntityFQ2_5boost33shared_ptr__tm__15_12ServerPlayer;
    undefPlayerFun stopSeenByPlayer__6EntityFQ2_5boost33shared_ptr__tm__15_12ServerPlayer;
    undefPlayerFun rotate__6EntityFP8Rotation;
    undefPlayerFun mirror__6EntityFP6Mirror;
    undefPlayerFun onlyOpCanSetNbt__6EntityFv;
    undefPlayerFun checkAndResetTeleportedFlag__6EntityFv;
    undefPlayerFun getControllingPassenger__6EntityFv;
    undefPlayerFun getPassengers__6EntityFv;
    undefPlayerFun hasPassenger__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun hasPassenger__6EntityFUL;
    undefPlayerFun __CPR215__fillIndirectPassengers__6EntityFULPQ2_3std170set__tm__158_Q2_5boost25shared_ptr__tm__8_J24JQ2_3std49less__tm__37_Q2_J61JJ67JQ2_3std54allocator__tm__J113J;
    undefPlayerFun getIndirectPassengers__6EntityFUL;
    undefPlayerFun getIndirectPassengers__6EntityFv;
    undefPlayerFun getRootVehicle__6EntityFv;
    undefPlayerFun isPassengerOfSameVehicle__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun hasIndirectPassenger__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun hasIndirectPassenger__6EntityFUL;
    undefPlayerFun isControlledByLocalInstance__6EntityFv;
    undefPlayerFun getVehicle__6EntityFv;
    undefPlayerFun getPistonPushReaction__6EntityFv;
    undefPlayerFun getSoundSource__6PlayerFv;
    undefPlayerFun isCreative__6EntityFv;
    undefPlayerFun isDespawnProtected__6EntityFv;
    undefPlayerFun setDespawnProtected__6EntityFv;
    undefPlayerFun couldWander__6EntityFv;
    undefPlayerFun canCreateParticles__6PlayerFv;
    undefPlayerFun stopCurrentLerp__12LivingEntityFv;
    undefPlayerFun PositionLocked__6PlayerFv;
    undefPlayerFun SetPositionLocked__6PlayerFb;
    undefPlayerFun TakeGlideCollisionDamage__6PlayerFv;
    undefPlayerFun SetGlideCollisionDamage__6PlayerFb;
    undefPlayerFun GetLiftForceModifier__6PlayerFv;
    undefPlayerFun SetLiftForceModifier__6PlayerFd;
    undefPlayerFun onLoadedFromSave__6EntityFv_9;
    undefPlayerFun isUsingItemFlag__6EntityFv_9;
    undefPlayerFun setUsingItemFlag__6EntityFb_9;
    undefPlayerFun DoAutoAttackOnTouch__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun startSpinAttack__6PlayerFv;
    undefPlayerFun stopSpinAttack__6PlayerFv;
    undefPlayerFun tickLeash__6EntityFv;
    undefPlayerFun dropLeash__6EntityFbT1;
    undefPlayerFun canBeLeashed__6EntityFRCQ2_5boost25shared_ptr__tm__8_6Player;
    undefPlayerFun isLeashed__6EntityFv;
    undefPlayerFun getLeashHolder__6EntityFv;
    undefPlayerFun isLeashedToPlayer__6EntityFRCQ2_5boost25shared_ptr__tm__8_6Player;
    undefPlayerFun setLeashedTo__6EntityFQ2_5boost25shared_ptr__tm__8_6Entityb;
    undefPlayerFun restoreLeashFromSave__6EntityFv;
    undefPlayerFun registerAttributes__6PlayerFv;
    undefPlayerFun isWaterMob__12LivingEntityFv;
    undefPlayerFun breathesWater__12LivingEntityFv;
    undefPlayerFun breathesAir__12LivingEntityFv;
    undefPlayerFun breathesLava__12LivingEntityFv;
    undefPlayerFun breathesSolids__12LivingEntityFv;
    undefPlayerFun GetSuffocateTime__6PlayerFv;
    undefPlayerFun GetInhaleTime__6PlayerFv;
    undefPlayerFun generatesBubbles__6PlayerFv;
    undefPlayerFun onChangedBlock__6PlayerFRC8BlockPos;
    undefPlayerFun isBaby__12LivingEntityFv;
    undefPlayerFun tickDeath__12LivingEntityFv;
    undefPlayerFun shouldDropExperience__12LivingEntityFv;
    undefPlayerFun decreaseAirSupply__12LivingEntityFi;
    undefPlayerFun getExperienceReward__6PlayerFQ2_5boost25shared_ptr__tm__8_6Player;
    undefPlayerFun isAlwaysExperienceDropper__6PlayerFv;
    undefPlayerFun getRandom__12LivingEntityFv;
    undefPlayerFun getLastHurtByMob__12LivingEntityFv;
    undefPlayerFun getLastHurtByMobTimestamp__12LivingEntityFv;
    undefPlayerFun __CPR77__setLastHurtByMob__12LivingEntityFQ2_5boost33shared_ptr__tm__15_J18J;
    undefPlayerFun getLastHurtMob__12LivingEntityFv;
    undefPlayerFun getLastHurtMobTimestamp__12LivingEntityFv;
    undefPlayerFun setLastHurtMob__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun getNoActionTime__12LivingEntityFv;
    undefPlayerFun tickEffects__12LivingEntityFv;
    undefPlayerFun updateInvisibilityStatus__12LivingEntityFv;
    undefPlayerFun removeEffectParticles__12LivingEntityFv;
    undefPlayerFun removeAllEffects__12LivingEntityFv;
    undefPlayerFun getActiveEffects__12LivingEntityFv;
    undefPlayerFun hasEffect__12LivingEntityFP9MobEffect;
    undefPlayerFun getEffect__12LivingEntityFP9MobEffect;
    undefPlayerFun addEffect__12LivingEntityFP17MobEffectInstanceRCQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun addEffectNoUpdate__12LivingEntityFP17MobEffectInstance;
    undefPlayerFun canBeAffected__12LivingEntityFP17MobEffectInstance;
    undefPlayerFun isInvertedHealAndHarm__12LivingEntityFv;
    undefPlayerFun removeEffectNoUpdate__12LivingEntityFP9MobEffect;
    undefPlayerFun removeEffect__12LivingEntityFP9MobEffect;
    undefPlayerFun onEffectAdded__12LivingEntityFP17MobEffectInstance;
    undefPlayerFun onEffectUpdated__12LivingEntityFP17MobEffectInstanceb;
    undefPlayerFun onEffectRemoved__12LivingEntityFP17MobEffectInstance;
    undefPlayerFun heal__12LivingEntityFf;
    undefPlayerFun getHealth__12LivingEntityFv;
    undefPlayerFun setHealth__12LivingEntityFf;
    undefPlayerFun getLastDamageSource__12LivingEntityFv;
    undefPlayerFun blockUsingShield__6PlayerFRCQ2_5boost33shared_ptr__tm__15_12LivingEntity;
    undefPlayerFun playHurtSound__12LivingEntityFPC12DamageSource;
    undefPlayerFun checkTotemDeathProtection__12LivingEntityFPC12DamageSource;
    undefPlayerFun isDamageSourceBlocked__12LivingEntityFPC12DamageSource;
    undefPlayerFun breakItem__12LivingEntityF35not_null_ptr__tm__15_12ItemInstance;
    undefPlayerFun die__6PlayerFPC12DamageSource;
    undefPlayerFun dropEquipment__12LivingEntityFbi;
    undefPlayerFun knockback__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6EntityfdT3;
    undefPlayerFun getHurtSound__6PlayerFPC12DamageSource;
    undefPlayerFun getDeathSound__6PlayerFv;
    undefPlayerFun getFallDamageSound__6PlayerFi;
    undefPlayerFun dropAllDeathLoot__12LivingEntityFbiPC12DamageSource;
    undefPlayerFun dropDeathLoot__12LivingEntityFbi;
    undefPlayerFun onLadder__12LivingEntityFv;
    undefPlayerFun isShootable__12LivingEntityFv;
    undefPlayerFun getArmorValue__12LivingEntityFv;
    undefPlayerFun hurtArmor__6PlayerFf;
    undefPlayerFun hurtCurrentlyUsedShield__6PlayerFf;
    undefPlayerFun getDamageAfterArmorAbsorb__12LivingEntityFPC12DamageSourcef;
    undefPlayerFun getDamageAfterMagicAbsorb__12LivingEntityFPC12DamageSourcef;
    undefPlayerFun actuallyHurt__6PlayerFPC12DamageSourcef;
    undefPlayerFun getCombatTracker__12LivingEntityFv;
    undefPlayerFun getKillCredit__12LivingEntityFv;
    undefPlayerFun getMaxHealth__12LivingEntityFv;
    undefPlayerFun getArrowCount__12LivingEntityFv;
    undefPlayerFun setArrowCount__12LivingEntityFi;
    undefPlayerFun swing__12LivingEntityFQ2_15InteractionHand16EInteractionHand;
    undefPlayerFun updateSwingTime__12LivingEntityFv;
    undefPlayerFun getAttribute__12LivingEntityFP9Attribute;
    undefPlayerFun getAttributes__12LivingEntityFv;
    undefPlayerFun getMobType__12LivingEntityFv;
    undefPlayerFun getMainHandItem__12LivingEntityFv;
    undefPlayerFun getOffhandItem__12LivingEntityFv;
    undefPlayerFun getItemInHand__12LivingEntityFQ2_15InteractionHand16EInteractionHand;
    undefPlayerFun setItemInHand__12LivingEntityFQ2_15InteractionHand16EInteractionHand35not_null_ptr__tm__15_12ItemInstance;
    undefPlayerFun hasItemInSlot__12LivingEntityFPC13EquipmentSlot;
    undefPlayerFun getItemSlot__6PlayerFPC13EquipmentSlot;
    undefPlayerFun getItemInHandIcon__6PlayerF35not_null_ptr__tm__15_12ItemInstancei;
    undefPlayerFun getSoundVolume__12LivingEntityFv;
    undefPlayerFun getVoicePitch__12LivingEntityFv;
    undefPlayerFun isImmobile__6PlayerFv;
    undefPlayerFun findStandUpPosition__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun getJumpPower__12LivingEntityFv;
    undefPlayerFun jumpFromGround__6PlayerFv;
    undefPlayerFun jumpInWater__12LivingEntityFv;
    undefPlayerFun goDownInWater__12LivingEntityFv;
    undefPlayerFun jumpInLava__12LivingEntityFv;
    undefPlayerFun getWaterSlowDown__12LivingEntityFv;
    undefPlayerFun travel__6PlayerFfN21;
    undefPlayerFun updateModelAnimation__12LivingEntityFv;
    undefPlayerFun getSpeed__6PlayerFv;
    undefPlayerFun setSpeed__12LivingEntityFf;
    undefPlayerFun doHurtTarget__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun isSleeping__6PlayerFv;
    undefPlayerFun tickHeadTurn__12LivingEntityFfT1;
    undefPlayerFun aiStep__6PlayerFv;
    undefPlayerFun serverAiStep__6PlayerFv;
    undefPlayerFun pushEntities__6PlayerFv;
    undefPlayerFun doPush__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun setJumping__12LivingEntityFb;
    undefPlayerFun take__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entityi;
    undefPlayerFun canSee__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun getAttackAnim__12LivingEntityFf;
    undefPlayerFun getSweptVolume__12LivingEntityFv;
    undefPlayerFun isEffectiveAi__12LivingEntityFv;
    undefPlayerFun getAbsorptionAmount__6PlayerFv;
    undefPlayerFun setAbsorptionAmount__6PlayerFf;
    undefPlayerFun onEnterCombat__12LivingEntityFv;
    undefPlayerFun onLeaveCombat__12LivingEntityFv;
    undefPlayerFun updateEffectVisibility__12LivingEntityFv;
    undefPlayerFun getMainArm__6PlayerFv;
    undefPlayerFun isUsingItem__12LivingEntityFv;
    undefPlayerFun getUsedItemHand__12LivingEntityFv;
    undefPlayerFun updatingUsingItem__12LivingEntityFv;
    undefPlayerFun startUsingItem__12LivingEntityFQ2_15InteractionHand16EInteractionHand;
    undefPlayerFun spawnItemUseParticles__12LivingEntityF35not_null_ptr__tm__15_12ItemInstancei;
    undefPlayerFun completeUsingItem__12LivingEntityFv;
    undefPlayerFun getTicksUsingItem__12LivingEntityFv;
    undefPlayerFun releaseUsingItem__12LivingEntityFv;
    undefPlayerFun releaseUsingItem__12LivingEntityFi;
    undefPlayerFun stopUsingItem__12LivingEntityFv;
    undefPlayerFun isBlocking__12LivingEntityFv;
    undefPlayerFun isFallFlying__12LivingEntityFv;
    undefPlayerFun getFallFlyingTicks__12LivingEntityFv;
    undefPlayerFun isAffectedByPotions__12LivingEntityFv;
    undefPlayerFun attackable__12LivingEntityFv;
    undefPlayerFun setRecordPlayingNearby__12LivingEntityFRC8BlockPosb;
    undefPlayerFun IsCreativeFlying__6PlayerFv;
    undefPlayerFun updateFrameTick__6PlayerFv;
    undefPlayerFun closeContainer__6PlayerFv;
    undefPlayerFun touch__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun getScore__6PlayerFv;
    undefPlayerFun setScore__6PlayerFi;
    undefPlayerFun increaseScore__6PlayerFi;
    undefPlayerFun drop__6PlayerFb;
    undefPlayerFun reallyDrop__6PlayerFQ2_5boost31shared_ptr__tm__13_10ItemEntity;
    undefPlayerFun GetThirdPersonView__6PlayerFb;
    undefPlayerFun SetThirdPersonView__6PlayerFi;
    undefPlayerFun CanChangeThirdPersonView__6PlayerFv;
    undefPlayerFun GetCameraController__6PlayerFv;
    undefPlayerFun SetCameraController__6PlayerFP16CameraControllerb;
    undefPlayerFun canHarmPlayer__6PlayerFQ2_5boost25shared_ptr__tm__8_6Player;
    undefPlayerFun canHarmPlayer__6PlayerFQ2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_w;
    undefPlayerFun getArmorCoverPercentage__6PlayerFv;
    undefPlayerFun openTextEdit__6PlayerFQ2_5boost36shared_ptr__tm__18_15SignBlockEntity;
    undefPlayerFun openMinecartCommandBlock__6PlayerFQ2_5boost37shared_ptr__tm__19_16BaseCommandBlock;
    undefPlayerFun openCommandBlock__6PlayerFQ2_5boost39shared_ptr__tm__21_18CommandBlockEntity;
    undefPlayerFun openTrading__6PlayerFQ2_5boost28shared_ptr__tm__10_8MerchantRCQ2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wi;
    undefPlayerFun openContainer__6PlayerFQ2_5boost29shared_ptr__tm__11_9Container;
    undefPlayerFun openHorseInventory__6PlayerFQ2_5boost34shared_ptr__tm__16_13AbstractHorseQ2_5boost29shared_ptr__tm__11_9Container;
    undefPlayerFun startBlockInteraction__6PlayerFR17InteractionObject;
    undefPlayerFun openItemInstanceGui__6PlayerF35not_null_ptr__tm__15_12ItemInstanceQ2_15InteractionHand16EInteractionHand;
    undefPlayerFun interactOn__6PlayerFQ2_5boost25shared_ptr__tm__8_6EntityQ2_15InteractionHand16EInteractionHand;
    undefPlayerFun attack__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun disableShield__6PlayerFb;
    undefPlayerFun crit__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun magicCrit__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun respawn__6PlayerFv;
    undefPlayerFun isLocalPlayer__6PlayerFv;
    undefPlayerFun getGameProfile__6PlayerFv;
    undefPlayerFun startSleepInBed__6PlayerFRC8BlockPosb;
    undefPlayerFun stopSleepInBed__6PlayerFbN21;
    undefPlayerFun displayClientMessage__6PlayerFib;
    undefPlayerFun getRespawnPosition__6PlayerFv;
    undefPlayerFun isRespawnForced__6PlayerFv;
    undefPlayerFun setRespawnPosition__6PlayerFP8BlockPosb;
    undefPlayerFun hasAchievement__6PlayerFP11Achievement;
    undefPlayerFun awardStat__6PlayerFP4Stat25arrayWithLength__tm__3_Uc;
    undefPlayerFun resetStat__6PlayerFP4Stat;
    undefPlayerFun checkMovementStatistiscs__6PlayerFdN21;
    undefPlayerFun increaseXp__6PlayerFi;
    undefPlayerFun getEnchantmentSeed__6PlayerFv;
    undefPlayerFun onEnchantmentPerformed__6PlayerFi;
    undefPlayerFun giveExperienceLevels__6PlayerFi;
    undefPlayerFun mayBuild__6PlayerFv;
    undefPlayerFun mayUseItemAt__6PlayerFRC8BlockPosPC9Direction35not_null_ptr__tm__15_12ItemInstance;
    undefPlayerFun onUpdateAbilities__6PlayerFv;
    undefPlayerFun setGameMode__6PlayerFPC8GameType;
    undefPlayerFun __pure_virtual_called;
    undefPlayerFun GetScoreboard__6PlayerFv;
    undefPlayerFun onCrafted__6PlayerF35not_null_ptr__tm__15_12ItemInstance;
    undefPlayerFun getTexture__6PlayerFv;
    undefPlayerFun setCustomSkin__6PlayerFUi;
    undefPlayerFun setCustomCape__6PlayerFUi;
    undefPlayerFun handleCollectItem__6PlayerF35not_null_ptr__tm__15_12ItemInstance;
    undefPlayerFun SetCamera__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefPlayerFun SpectatePlayerNext__6PlayerFv;
    undefPlayerFun SpectatePlayerPrev__6PlayerFv;
    undefPlayerFun StopSpectatingPlayer__6PlayerFv;
    undefPlayerFun IsSpectatingOtherPlayer__6PlayerFv;
    undefPlayerFun __pure_virtual_called2;
    undefPlayerFun GetGameMode__6PlayerFv;



};


typedef struct ServerPlayer ServerPlayer, *PServerPlayer;
typedef struct ServerPlayer_vtbl ServerPlayer_vtbl, *PServerPlayer_vtbl;

struct ServerPlayer {
    ServerPlayer_vtbl *__vftable;
};
struct ServerPlayer_vtbl {
    undefPlayerFun FUN_818492da;
undefPlayerFun FUN_81849552;
undefPlayerFun FUN_81856a9e;
undefPlayerFun FUN_81856c36;
undefPlayerFun LAB_8133d616;
undefPlayerFun FUN_81856e5c;
undefPlayerFun LAB_81180602;
undefPlayerFun LAB_81180616;
undefPlayerFun FUN_8118061c;
undefPlayerFun FUN_8133e9d0;
undefPlayerFun FUN_811806dc;
undefPlayerFun LAB_811808e4;
undefPlayerFun LAB_81ae5040;
undefPlayerFun LivingEntity__fjDerivedCtorCalls;
undefPlayerFun LivingEntity__kill;
undefPlayerFun Player__defineSynchedData;
undefPlayerFun Player__resetPos;
undefPlayerFun Player__remove;
undefPlayerFun LAB_8116eb20;
undefPlayerFun Entity__setSize;
undefPlayerFun Entity__setPos;
undefPlayerFun ServerPlayer__tick;
undefPlayerFun FUN_8127bff6;
undefPlayerFun LAB_818574a2;
undefPlayerFun LAB_81331262;
undefPlayerFun FUN_8116f98a;
undefPlayerFun LAB_8116fbba;
undefPlayerFun FUN_81284c02;
undefPlayerFun Entity__move;
undefPlayerFun Entity__updateDeltaAfterMove;
undefPlayerFun LAB_81172170;
undefPlayerFun LAB_8133127e;
undefPlayerFun LAB_8133128a;
undefPlayerFun LAB_81331296;
undefPlayerFun FUN_811721ce;
undefPlayerFun LAB_81172456;
undefPlayerFun Entity__playStepSound;
undefPlayerFun Entity__playUnderwaterSound;
undefPlayerFun LAB_81172ae6;
undefPlayerFun LAB_81172aee;
undefPlayerFun Player__playSound;
undefPlayerFun LAB_81172c94;
undefPlayerFun LAB_81172cb4;
undefPlayerFun LAB_81172cf8;
undefPlayerFun FUN_81172d18;
undefPlayerFun LAB_81172d5c;
undefPlayerFun LAB_81172d7c;
undefPlayerFun LAB_8133d5ea;
undefPlayerFun LAB_8184e810;
undefPlayerFun LAB_81172f96;
undefPlayerFun LAB_81172f9a;
undefPlayerFun LAB_8133c1aa;
undefPlayerFun LAB_811732c0;
undefPlayerFun LAB_811732c6;
undefPlayerFun FUN_811732cc;
undefPlayerFun FUN_81173512;
undefPlayerFun FUN_8133c2fc;
undefPlayerFun FUN_8117416c;
undefPlayerFun FUN_81174196;
undefPlayerFun FUN_81174314;
undefPlayerFun FUN_81174584;
undefPlayerFun FUN_812884e4;
undefPlayerFun LAB_81174a8a;
undefPlayerFun FUN_81174b62;
undefPlayerFun Entity__moveAgain;
undefPlayerFun LAB_81174f36;
undefPlayerFun FUN_8133f2ec;
undefPlayerFun LAB_81175192;
undefPlayerFun FUN_8128b534;
undefPlayerFun ServerPlayer__hurt;
undefPlayerFun LAB_8128b3b4;
undefPlayerFun FUN_81a01554;
undefPlayerFun FUN_8128b50e;
undefPlayerFun LAB_8117562c;
undefPlayerFun LAB_8117562e;
undefPlayerFun Entity__shouldRender;
undefPlayerFun FUN_8132f550;
undefPlayerFun Entity__save;
undefPlayerFun FUN_81176a5c;
undefPlayerFun LAB_8132f5b4;
undefPlayerFun LAB_81177c9c;
undefPlayerFun FUN_81849562;
undefPlayerFun ServerPlayer__addAdditonalSaveData;
undefPlayerFun LAB_81974364;
undefPlayerFun FUN_81177ca0;
undefPlayerFun FUN_81177ca4;
undefPlayerFun FUN_81177cb6;
undefPlayerFun FUN_81177e86;
undefPlayerFun LAB_812838fc;
undefPlayerFun LAB_8133a862;
undefPlayerFun FUN_811784e0;
undefPlayerFun LAB_811784e4;
undefPlayerFun Player__rideTick;
undefPlayerFun FUN_8117893c;
undefPlayerFun LAB_81178be8;
undefPlayerFun LAB_81338090;
undefPlayerFun FUN_81178bf4;
undefPlayerFun FUN_81178c06;
undefPlayerFun FUN_8184e2ca;
undefPlayerFun FUN_81178d48;
undefPlayerFun FUN_81179420;
undefPlayerFun LAB_8117956a;
undefPlayerFun LAB_8117957e;
undefPlayerFun LAB_81179582;
undefPlayerFun FUN_8117958e;
undefPlayerFun FUN_8184e586;
undefPlayerFun FUN_8184e6f6;
undefPlayerFun FUN_81179edc;
undefPlayerFun FUN_8117a832;
undefPlayerFun FUN_8117ae36;
undefPlayerFun FUN_8128afba;
undefPlayerFun LAB_8117ae92;
undefPlayerFun LAB_8117ae9a;
undefPlayerFun LAB_8117af1e;
undefPlayerFun Entity__getForward;
undefPlayerFun FUN_8117af3e;
undefPlayerFun LAB_813312a2;
undefPlayerFun LAB_8117b100;
undefPlayerFun Player__handleEntityEvent;
undefPlayerFun LivingEntity__animateHurt;
undefPlayerFun FUN_8133df72;
undefPlayerFun FUN_8133e186;
undefPlayerFun FUN_8117b190;
undefPlayerFun FUN_8133d8b0;
undefPlayerFun Entity__isOnFire;
undefPlayerFun Entity__isPassenger;
undefPlayerFun Entity__isVehicle;
undefPlayerFun Entity__isSneaking;
undefPlayerFun Entity__setSneaking;
undefPlayerFun LAB_8117b7f6;
undefPlayerFun Entity__setIsIdle;
undefPlayerFun LAB_8117b8a4;
undefPlayerFun FUN_812853b8;
undefPlayerFun Entity__isSwimming;
undefPlayerFun LAB_8117b97c;
undefPlayerFun Entity__startSwimming;
undefPlayerFun FUN_8117b9f2;
undefPlayerFun FUN_8117ba48;
undefPlayerFun LAB_8117bae6;
undefPlayerFun Entity__getDamageNearbyMobs;
undefPlayerFun LAB_8117bb92;
undefPlayerFun Entity__setGlowing;
undefPlayerFun FUN_8117bc5e;
undefPlayerFun Player__isInvisibleTo;
undefPlayerFun FUN_8133e39e;
undefPlayerFun FUN_8117be88;
undefPlayerFun FUN_8117bea4;
undefPlayerFun Player__setInvisible;
undefPlayerFun FUN_81a014f0;
undefPlayerFun Entity__canFly;
undefPlayerFun FUN_8134196a;
undefPlayerFun Entity__getMaxAirSupply;
undefPlayerFun FUN_8117c2e6;
undefPlayerFun Entity__thunderHit;
undefPlayerFun Entity__onAboveBubbleCol;
undefPlayerFun Player__killed;
undefPlayerFun Entity__checkInBlock;
undefPlayerFun LivingEntity__spawnEatParticles;
undefPlayerFun Player__makeStuckInWeb;
wchar_t* (*Player__getName)(ServerPlayer* player, wchar_t* strOut);

};


static void logPlayerInfo(Player* player, int* playerAdd){
    logInfo("%llu", GetTick());
    if(player == NULL){
        logInfo("Player null");
        return;
    }
    //print_bytes(playerAdd,0x40);

    logInfo("player: %08X", (int)(int*)player);
    logInfo("playerAdd: %08X", (int)playerAdd);

    logInfo("angle1: %.4f", player->angle1);
    logInfo("angle2: %.4f", player->angle2	);
    logInfo("angle3: %.4f", player->angle3	);
    logInfo("angle4: %.4f", player->angle4	);
    logInfo("angle5: %.4f", player->angle5	);
    logInfo("angle6: %.4f", player->angle6	);
    logInfo("angleA: %.4f", player->angleA	);
    logInfo("angleB: %.4f", player->angleB	);

    logInfo("posx1: %.2f", player->posx1);
    logInfo("posy1: %.2f", player->posy1);
    logInfo("posz1: %.2f", player->posz1);

    logInfo("posx2: %.2f", player->posx2);
    logInfo("posy2: %.2f", player->posy2);
    logInfo("posz2: %.2f", player->posz2);

    logInfo("posx3: %.2f", player->posx3);
    logInfo("posy3: %.2f", player->posy3);
    logInfo("posz3: %.2f", player->posz3);
    
    logInfo("posx4: %.2f", player->posx4);
    logInfo("posy4: %.2f", player->posy4);
    logInfo("posz4: %.2f", player->posz4);
    
    logInfo("posx5: %.2f", player->posx5);
    logInfo("posy5: %.2f", player->posy5);
    logInfo("posz5: %.2f", player->posz5);

    logInfo("0: %08X", swap(playerAdd[0x52]));


    logInfo("A: %.2f|%.2f|%.2f", *(float*)&playerAdd[0x52], *(float*)&playerAdd[0x53], *(float*)&playerAdd[0x54]);
    logInfo("B: %.2f|%.2f|%.2f", *(float*)&playerAdd[0x100], *(float*)&playerAdd[0x101], *(float*)&playerAdd[0x102]);
}

#endif