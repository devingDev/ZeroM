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
#define undefinedFunction FunctionType

struct Player_vtbl { /* vtable of Player */
    char pad00[0x34]; // 0x0
    undefinedFunction fjDerivedCtorCalls__12LivingEntityFv; //fjDerivedCtorCalls__12LivingEntityFv
    undefinedFunction kill__12LivingEntityFv; //kill__12LivingEntityFv
    undefinedFunction defineSynchedData__6PlayerFv; //defineSynchedData__6PlayerFv
    undefinedFunction resetPos__6PlayerFv; //resetPos__6PlayerFv
    undefinedFunction remove__6PlayerFv; //remove__6PlayerFv
    undefinedFunction setDropContainerContent__6EntityFb; //setDropContainerContent__6EntityFb
    undefinedFunction setSize__6EntityFfT1; //setSize__6EntityFfT1
    undefinedFunction setPos__6EntityFdN21; //setPos__6EntityFdN21
    undefinedFunction tick__6PlayerFv; //tick__6PlayerFv
    undefinedFunction baseTick__12LivingEntityFv; //baseTick__12LivingEntityFv
    undefinedFunction processDimensionDelay__6EntityFv; //processDimensionDelay__6EntityFv
    undefinedFunction getPortalWaitTime__6PlayerFv; //getPortalWaitTime__6PlayerFv
    undefinedFunction setSecondsOnFire__6EntityFi; //setSecondsOnFire__6EntityFi
    undefinedFunction clearFire__6EntityFv; //clearFire__6EntityFv
    undefinedFunction outOfWorld__12LivingEntityFv; //outOfWorld__12LivingEntityFv
    undefinedFunction move__6EntityF9MoverTypedN22b; //move__6EntityF9MoverTypedN22b
    undefinedFunction updateDeltaAfterMove__6EntityFP5BlockdN22RdN25; //updateDeltaAfterMove__6EntityFP5BlockdN22RdN25
    undefinedFunction setLocationFromBoundingbox__6EntityFv; //setLocationFromBoundingbox__6EntityFv
    undefinedFunction getSwimSound__6PlayerFv; //getSwimSound__6PlayerFv
    undefinedFunction getSwimSplashSound__6PlayerFv; //getSwimSplashSound__6PlayerFv
    undefinedFunction getHeavySplashSound__6PlayerFv; //getHeavySplashSound__6PlayerFv
    undefinedFunction checkInsideBlocks__6EntityFv; //checkInsideBlocks__6EntityFv
    undefinedFunction onInsideBlock__6EntityFPC10BlockState; //onInsideBlock__6EntityFPC10BlockState
    undefinedFunction playStepSound__6EntityFRC8BlockPosP5Block; //playStepSound__6EntityFRC8BlockPosP5Block
    undefinedFunction playUnderwaterSound__6EntityFRC8BlockPosP5Block; //playUnderwaterSound__6EntityFRC8BlockPosP5Block
    undefinedFunction playFlySound__6EntityFf; //playFlySound__6EntityFf
    undefinedFunction makeFlySound__6EntityFv; //makeFlySound__6EntityFv
    undefinedFunction playSound__6PlayerFPC10SoundEventfT2; //playSound__6PlayerFPC10SoundEventfT2
    undefinedFunction isSilent__6EntityFv; //isSilent__6EntityFv
    undefinedFunction setSilent__6EntityFb; //setSilent__6EntityFb
    undefinedFunction isNoGravity__6EntityFv; //isNoGravity__6EntityFv
    undefinedFunction setNoGravity__6EntityFb; //setNoGravity__6EntityFb
    undefinedFunction isMoving__6EntityFv; //isMoving__6EntityFv
    undefinedFunction setMoving__6EntityFb; //setMoving__6EntityFb
    undefinedFunction makeStepSound__6PlayerFv; //makeStepSound__6PlayerFv
    undefinedFunction checkFallDamage__12LivingEntityFdbP5BlockRC8BlockPos; //checkFallDamage__12LivingEntityFdbP5BlockRC8BlockPos
    undefinedFunction getCollideBox__6EntityFv; //getCollideBox__6EntityFv
    undefinedFunction burn__6EntityFi; //burn__6EntityFi
    undefinedFunction causeFallDamage__6PlayerFfT1; //causeFallDamage__6PlayerFfT1
    undefinedFunction isInWater__6EntityFv; //isInWater__6EntityFv
    undefinedFunction headInWater__6EntityFv; //headInWater__6EntityFv
    undefinedFunction isOverWater__6EntityFv; //isOverWater__6EntityFv
    undefinedFunction updateInWaterState__6EntityFv; //updateInWaterState__6EntityFv
    undefinedFunction doWaterSplashEffect__6PlayerFv; //doWaterSplashEffect__6PlayerFv
    undefinedFunction updateSprintingState;
    undefinedFunction doSprintParticleEffect; // 0xE8
    
    undefRet (*isUnderLiquid)(Player* player, int a1); // 0xEC
    undefRet (*isInLiquid)(Player* player, int a1, double *a2); // 0xF0
    undefRet (*getLightColor)(Player* player); // 0xF4
    double (*getBrightness) (Player* player); // 0xF8
    undefRet (*setLevel) (Player* player, int a1); // 0xFC


    int (*moveTo)(Player* player, double x, double y, double z, double angle1, double angle2); // 0x100

    undefinedFunction playerTouch__6EntityFQ2_5boost25shared_ptr__tm__8_6Player; // 0x104
    undefinedFunction push__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction push__6EntityFdN21;
    undefinedFunction markHurt__12LivingEntityFv;
    undefinedFunction hurt__6PlayerFPC12DamageSourcef;
    undefinedFunction getViewVector__12LivingEntityFf;
    undefinedFunction isPickable__6PlayerFv;
    undefinedFunction isPushable__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction awardKillScore__6EntityFQ2_5boost25shared_ptr__tm__8_6EntityiPC12DamageSource;
    undefinedFunction shouldRender__6EntityFdN21;
    undefinedFunction shouldRender__6EntityFd;
    undefinedFunction shouldRenderAtSqrDistance__6PlayerFd;
    undefinedFunction save__6EntityFP11CompoundTag;
    undefinedFunction load__6EntityFP11CompoundTag;
    undefinedFunction shouldTick__6PlayerFv;
    undefinedFunction repositionEntityAfterLoad__6EntityFv;
    undefinedFunction readAdditionalSaveData__6PlayerFP11CompoundTag;
    undefinedFunction addAdditonalSaveData__6PlayerFP11CompoundTag;
    undefinedFunction readAdditionContructionTag__6EntityFP11CompoundTag_9;
    undefinedFunction getAdditionContructionTag__6EntityFv;
    undefinedFunction spawnAtLocation__6EntityFP4Itemi;
    undefinedFunction spawnAtLocation__6EntityFP4Itemif;
    undefinedFunction spawnAtLocation__6EntityF35not_null_ptr__tm__15_12ItemInstancef;
    undefinedFunction isAlive__12LivingEntityFv;
    undefinedFunction isInWall__6PlayerFv;
    undefinedFunction interact__6EntityFRCQ2_5boost25shared_ptr__tm__8_6PlayerQ2_15InteractionHand16EInteractionHand;
    undefinedFunction getCollideAgainstBox__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction rideTick__6PlayerFv;
    undefinedFunction positionRider__6EntityFRCQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction onPassengerTurned__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction getRidingHeight__6PlayerFv;
    undefinedFunction getRideHeight__6EntityFv;
    undefinedFunction showVehicleHealth__6EntityFv;
    undefinedFunction startRiding__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction startRiding__6EntityFQ2_5boost25shared_ptr__tm__8_6Entityb;
    undefinedFunction GetInteractTooltip__6EntityFRC23EntityTooltipDataHolder;
    undefinedFunction GetHitTooltip__6EntityFRC23EntityTooltipDataHolder;
    undefinedFunction HideUseTooltips__6EntityFv;
    undefinedFunction canRide__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction ejectPassengers__6EntityFv;
    undefinedFunction stopRiding__6PlayerFv;
    undefinedFunction stopRidingBeforeTeleport__6EntityFv;
    undefinedFunction addPassenger__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction removePassenger__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction canAddPassenger__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction lerpTo__12LivingEntityFdN21fT4ib;
    undefinedFunction getPickRadius__6EntityFv;
    undefinedFunction getLookAngle__6EntityFv;
    undefinedFunction getRotationVector__6EntityFv; // 0x1C4

    Vec3* (*getForward)(Player* player); // 0x1C8

    undefinedFunction handleInsidePortal__6EntityFRC8BlockPos; // 0x1CC
    undefinedFunction getDimensionChangingDelay__6PlayerFv;
    undefinedFunction lerpMotion__6EntityFdN21;
    undefinedFunction handleEntityEvent__6PlayerFUci;
    undefinedFunction animateHurt__12LivingEntityFv;
    undefinedFunction getHandSlots__6PlayerFv;
    undefinedFunction getArmorSlots__6PlayerFv;
    undefinedFunction getAllSlots__6EntityFv;
    undefinedFunction setItemSlot__6PlayerFPC13EquipmentSlot35not_null_ptr__tm__15_12ItemInstance;
    undefinedFunction isOnFire__6EntityFv;
    undefinedFunction isPassenger__6EntityFv;
    undefinedFunction isVehicle__6EntityFv;
    undefinedFunction isSneaking__6EntityFv;
    undefinedFunction setSneaking__6EntityFb;
    undefinedFunction isIdle__6EntityFv;
    undefinedFunction setIsIdle__6EntityFb;
    undefinedFunction isSprinting__6EntityFv;
    undefinedFunction setSprinting__12LivingEntityFb;
    undefinedFunction isSwimming__6EntityFv;
    undefinedFunction isSwimmer__6EntityFv;
    undefinedFunction startSwimming__6EntityFv;
    undefinedFunction stopSwimming__6EntityFv;
    undefinedFunction setSwimmer__6EntityFb;
    undefinedFunction setDamageNearbyMobs__6EntityFb;
    undefinedFunction getDamageNearbyMobs__6EntityFv;
    undefinedFunction isGlowing__6EntityFv;
    undefinedFunction setGlowing__6EntityFb;
    undefinedFunction isInvisible__6EntityFv;
    undefinedFunction isInvisibleTo__6PlayerFQ2_5boost25shared_ptr__tm__8_6Player;
    undefinedFunction getTeam__6PlayerFv;
    undefinedFunction isAlliedTo__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction isAlliedTo__6EntityFP4Team;
    undefinedFunction setInvisible__6PlayerFb;
    undefinedFunction ShouldRenderShadow__6PlayerFv;
    undefinedFunction canFly__6EntityFv;
    undefinedFunction getAttachPos__6PlayerFQ2_6Entity15EEntityLocationf;
    undefinedFunction getMaxAirSupply__6EntityFv;
    undefinedFunction setAirSupply__6EntityFi;
    undefinedFunction thunderHit__6EntityFPC13LightningBolt;
    undefinedFunction onAboveBubbleCol__6EntityFb;
    undefinedFunction killed__6PlayerFQ2_5boost33shared_ptr__tm__15_12LivingEntity;
    undefinedFunction checkInBlock__6EntityFdN21;
    undefinedFunction spawnEatParticles__12LivingEntityFRC12ItemInstancei;
    undefinedFunction makeStuckInWeb__6PlayerFv;
    undefinedFunction getName__6PlayerFv;
    undefinedFunction isInvulnerableTo__6EntityFPC12DamageSource;
    undefinedFunction isInvulnerable__6EntityFv;
    undefinedFunction setInvulnerable__6EntityFb;
    undefinedFunction getSubEntities__6EntityFv;
    undefinedFunction is__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction getYHeadRot__12LivingEntityFv;
    undefinedFunction setYHeadRot__12LivingEntityFf;
    undefinedFunction setYBodyRot__12LivingEntityFf;
    undefinedFunction isAttackable__6EntityFv;
    undefinedFunction skipAttackInteraction__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction copyPosition__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction changeDimension__6EntityFi;
    undefinedFunction canChangeDimensions__6EntityFv;
    undefinedFunction getBlockExplosionResistance__6EntityFP9ExplosionP5LevelRC8BlockPos;
    undefinedFunction shouldBlockExplode__6EntityFP9ExplosionP5LevelRC8BlockPosf;
    undefinedFunction getMaxFallDistance__6EntityFv;
    undefinedFunction getPortalEntranceBlock__6EntityFv;
    undefinedFunction getPortalEntranceOffset__6EntityFv;
    undefinedFunction getPortalEntranceForwards__6EntityFv;
    undefinedFunction isIgnoringBlockTriggers__6EntityFv;
    undefinedFunction displayFireAnimation__6EntityFv;
    undefinedFunction setUUID__6EntityFRCQ2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_w;
    undefinedFunction getUUID__6EntityFv;
    undefinedFunction getStringUUID__6EntityFv;
    undefinedFunction isPushedByWater__6PlayerFv;
    undefinedFunction getViewScale__6EntityFv;
    undefinedFunction setViewScale__6EntityFd;
    undefinedFunction getDisplayOrNetworkNam;
    
    // one of these functions is missing on psvita! i left them here as comments, because on wiiu its different
    // undefinedFunction getDisplayName__6PlayerFv;
    // undefinedFunction getNetworkName__6PlayerFv; 
    undefinedFunction setCustomName__6EntityFRCQ2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wT1b;
    undefinedFunction getCustomName__6EntityFv;
    undefinedFunction hasCustomName__6EntityFv;
    undefinedFunction setCustomNameVisible__6EntityFb;
    undefinedFunction isCustomNameVisible__6EntityFv;
    
    int (*teleportTo)(Player* player, double x, double y, double z); // 0x304

    undefinedFunction shouldShowName__6PlayerFv;
    undefinedFunction onSyncedDataUpdated__6PlayerFPC23EntityDataAccessor_Base;
    undefinedFunction getDirection__6EntityFv;
    undefinedFunction getMotionDirection__6EntityFv;
    undefinedFunction broadcastToPlayer__6EntityFQ2_5boost33shared_ptr__tm__15_12ServerPlayer;
    undefinedFunction getBoundingBoxForCulling__6EntityFv;
    undefinedFunction setBoundingBox__12LivingEntityFP4AABB;
    undefinedFunction getEyeHeight__6PlayerFv;
    undefinedFunction setSlot__6PlayerFiRC35not_null_ptr__tm__15_12ItemInstance;
    undefinedFunction sendMessage__6PlayerFQ2_21ClientboundChatPacket18EChatPacketMessagePiUiPQ2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wT3;
    undefinedFunction hasPermission__6EntityF12EGameCommand;
    undefinedFunction getCommandSenderBlockPosition__6EntityFv;
    undefinedFunction getCommandSenderWorldPosition__6EntityFv;
    undefinedFunction getCommandSenderWorld__6EntityFv;
    undefinedFunction getCommandSenderEntity__6EntityFv;
    undefinedFunction isSendMessageEnabled__6PlayerFv;
    undefinedFunction setCommandStats__6EntityFQ2_12CommandStats15CommandStatTypei;
    undefinedFunction getServer__6EntityFv;
    undefinedFunction interactAt__6EntityFRCQ2_5boost25shared_ptr__tm__8_6PlayerP4Vec3Q2_15InteractionHand16EInteractionHand;
    undefinedFunction ignoreExplosion__6EntityFv;
    undefinedFunction startSeenByPlayer__6EntityFQ2_5boost33shared_ptr__tm__15_12ServerPlayer;
    undefinedFunction stopSeenByPlayer__6EntityFQ2_5boost33shared_ptr__tm__15_12ServerPlayer;
    undefinedFunction rotate__6EntityFP8Rotation;
    undefinedFunction mirror__6EntityFP6Mirror;
    undefinedFunction onlyOpCanSetNbt__6EntityFv;
    undefinedFunction checkAndResetTeleportedFlag__6EntityFv;
    undefinedFunction getControllingPassenger__6EntityFv;
    undefinedFunction getPassengers__6EntityFv;
    undefinedFunction hasPassenger__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction hasPassenger__6EntityFUL;
    undefinedFunction __CPR215__fillIndirectPassengers__6EntityFULPQ2_3std170set__tm__158_Q2_5boost25shared_ptr__tm__8_J24JQ2_3std49less__tm__37_Q2_J61JJ67JQ2_3std54allocator__tm__J113J;
    undefinedFunction getIndirectPassengers__6EntityFUL;
    undefinedFunction getIndirectPassengers__6EntityFv;
    undefinedFunction getRootVehicle__6EntityFv;
    undefinedFunction isPassengerOfSameVehicle__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction hasIndirectPassenger__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction hasIndirectPassenger__6EntityFUL;
    undefinedFunction isControlledByLocalInstance__6EntityFv;
    undefinedFunction getVehicle__6EntityFv;
    undefinedFunction getPistonPushReaction__6EntityFv;
    undefinedFunction getSoundSource__6PlayerFv;
    undefinedFunction isCreative__6EntityFv;
    undefinedFunction isDespawnProtected__6EntityFv;
    undefinedFunction setDespawnProtected__6EntityFv;
    undefinedFunction couldWander__6EntityFv;
    undefinedFunction canCreateParticles__6PlayerFv;
    undefinedFunction stopCurrentLerp__12LivingEntityFv;
    undefinedFunction PositionLocked__6PlayerFv;
    undefinedFunction SetPositionLocked__6PlayerFb;
    undefinedFunction TakeGlideCollisionDamage__6PlayerFv;
    undefinedFunction SetGlideCollisionDamage__6PlayerFb;
    undefinedFunction GetLiftForceModifier__6PlayerFv;
    undefinedFunction SetLiftForceModifier__6PlayerFd;
    undefinedFunction onLoadedFromSave__6EntityFv_9;
    undefinedFunction isUsingItemFlag__6EntityFv_9;
    undefinedFunction setUsingItemFlag__6EntityFb_9;
    undefinedFunction DoAutoAttackOnTouch__6EntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction startSpinAttack__6PlayerFv;
    undefinedFunction stopSpinAttack__6PlayerFv;
    undefinedFunction tickLeash__6EntityFv;
    undefinedFunction dropLeash__6EntityFbT1;
    undefinedFunction canBeLeashed__6EntityFRCQ2_5boost25shared_ptr__tm__8_6Player;
    undefinedFunction isLeashed__6EntityFv;
    undefinedFunction getLeashHolder__6EntityFv;
    undefinedFunction isLeashedToPlayer__6EntityFRCQ2_5boost25shared_ptr__tm__8_6Player;
    undefinedFunction setLeashedTo__6EntityFQ2_5boost25shared_ptr__tm__8_6Entityb;
    undefinedFunction restoreLeashFromSave__6EntityFv;
    undefinedFunction registerAttributes__6PlayerFv;
    undefinedFunction isWaterMob__12LivingEntityFv;
    undefinedFunction breathesWater__12LivingEntityFv;
    undefinedFunction breathesAir__12LivingEntityFv;
    undefinedFunction breathesLava__12LivingEntityFv;
    undefinedFunction breathesSolids__12LivingEntityFv;
    undefinedFunction GetSuffocateTime__6PlayerFv;
    undefinedFunction GetInhaleTime__6PlayerFv;
    undefinedFunction generatesBubbles__6PlayerFv;
    undefinedFunction onChangedBlock__6PlayerFRC8BlockPos;
    undefinedFunction isBaby__12LivingEntityFv;
    undefinedFunction tickDeath__12LivingEntityFv;
    undefinedFunction shouldDropExperience__12LivingEntityFv;
    undefinedFunction decreaseAirSupply__12LivingEntityFi;
    undefinedFunction getExperienceReward__6PlayerFQ2_5boost25shared_ptr__tm__8_6Player;
    undefinedFunction isAlwaysExperienceDropper__6PlayerFv;
    undefinedFunction getRandom__12LivingEntityFv;
    undefinedFunction getLastHurtByMob__12LivingEntityFv;
    undefinedFunction getLastHurtByMobTimestamp__12LivingEntityFv;
    undefinedFunction __CPR77__setLastHurtByMob__12LivingEntityFQ2_5boost33shared_ptr__tm__15_J18J;
    undefinedFunction getLastHurtMob__12LivingEntityFv;
    undefinedFunction getLastHurtMobTimestamp__12LivingEntityFv;
    undefinedFunction setLastHurtMob__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction getNoActionTime__12LivingEntityFv;
    undefinedFunction tickEffects__12LivingEntityFv;
    undefinedFunction updateInvisibilityStatus__12LivingEntityFv;
    undefinedFunction removeEffectParticles__12LivingEntityFv;
    undefinedFunction removeAllEffects__12LivingEntityFv;
    undefinedFunction getActiveEffects__12LivingEntityFv;
    undefinedFunction hasEffect__12LivingEntityFP9MobEffect;
    undefinedFunction getEffect__12LivingEntityFP9MobEffect;
    undefinedFunction addEffect__12LivingEntityFP17MobEffectInstanceRCQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction addEffectNoUpdate__12LivingEntityFP17MobEffectInstance;
    undefinedFunction canBeAffected__12LivingEntityFP17MobEffectInstance;
    undefinedFunction isInvertedHealAndHarm__12LivingEntityFv;
    undefinedFunction removeEffectNoUpdate__12LivingEntityFP9MobEffect;
    undefinedFunction removeEffect__12LivingEntityFP9MobEffect;
    undefinedFunction onEffectAdded__12LivingEntityFP17MobEffectInstance;
    undefinedFunction onEffectUpdated__12LivingEntityFP17MobEffectInstanceb;
    undefinedFunction onEffectRemoved__12LivingEntityFP17MobEffectInstance;
    undefinedFunction heal__12LivingEntityFf;
    undefinedFunction getHealth__12LivingEntityFv;
    undefinedFunction setHealth__12LivingEntityFf;
    undefinedFunction getLastDamageSource__12LivingEntityFv;
    undefinedFunction blockUsingShield__6PlayerFRCQ2_5boost33shared_ptr__tm__15_12LivingEntity;
    undefinedFunction playHurtSound__12LivingEntityFPC12DamageSource;
    undefinedFunction checkTotemDeathProtection__12LivingEntityFPC12DamageSource;
    undefinedFunction isDamageSourceBlocked__12LivingEntityFPC12DamageSource;
    undefinedFunction breakItem__12LivingEntityF35not_null_ptr__tm__15_12ItemInstance;
    undefinedFunction die__6PlayerFPC12DamageSource;
    undefinedFunction dropEquipment__12LivingEntityFbi;
    undefinedFunction knockback__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6EntityfdT3;
    undefinedFunction getHurtSound__6PlayerFPC12DamageSource;
    undefinedFunction getDeathSound__6PlayerFv;
    undefinedFunction getFallDamageSound__6PlayerFi;
    undefinedFunction dropAllDeathLoot__12LivingEntityFbiPC12DamageSource;
    undefinedFunction dropDeathLoot__12LivingEntityFbi;
    undefinedFunction onLadder__12LivingEntityFv;
    undefinedFunction isShootable__12LivingEntityFv;
    undefinedFunction getArmorValue__12LivingEntityFv;
    undefinedFunction hurtArmor__6PlayerFf;
    undefinedFunction hurtCurrentlyUsedShield__6PlayerFf;
    undefinedFunction getDamageAfterArmorAbsorb__12LivingEntityFPC12DamageSourcef;
    undefinedFunction getDamageAfterMagicAbsorb__12LivingEntityFPC12DamageSourcef;
    undefinedFunction actuallyHurt__6PlayerFPC12DamageSourcef;
    undefinedFunction getCombatTracker__12LivingEntityFv;
    undefinedFunction getKillCredit__12LivingEntityFv;
    undefinedFunction getMaxHealth__12LivingEntityFv;
    undefinedFunction getArrowCount__12LivingEntityFv;
    undefinedFunction setArrowCount__12LivingEntityFi;
    undefinedFunction swing__12LivingEntityFQ2_15InteractionHand16EInteractionHand;
    undefinedFunction updateSwingTime__12LivingEntityFv;
    undefinedFunction getAttribute__12LivingEntityFP9Attribute;
    undefinedFunction getAttributes__12LivingEntityFv;
    undefinedFunction getMobType__12LivingEntityFv;
    undefinedFunction getMainHandItem__12LivingEntityFv;
    undefinedFunction getOffhandItem__12LivingEntityFv;
    undefinedFunction getItemInHand__12LivingEntityFQ2_15InteractionHand16EInteractionHand;
    undefinedFunction setItemInHand__12LivingEntityFQ2_15InteractionHand16EInteractionHand35not_null_ptr__tm__15_12ItemInstance;
    undefinedFunction hasItemInSlot__12LivingEntityFPC13EquipmentSlot;
    undefinedFunction getItemSlot__6PlayerFPC13EquipmentSlot;
    undefinedFunction getItemInHandIcon__6PlayerF35not_null_ptr__tm__15_12ItemInstancei;
    undefinedFunction getSoundVolume__12LivingEntityFv;
    undefinedFunction getVoicePitch__12LivingEntityFv;
    undefinedFunction isImmobile__6PlayerFv;
    undefinedFunction findStandUpPosition__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction getJumpPower__12LivingEntityFv;
    undefinedFunction jumpFromGround__6PlayerFv;
    undefinedFunction jumpInWater__12LivingEntityFv;
    undefinedFunction goDownInWater__12LivingEntityFv;
    undefinedFunction jumpInLava__12LivingEntityFv;
    undefinedFunction getWaterSlowDown__12LivingEntityFv;
    undefinedFunction travel__6PlayerFfN21;
    undefinedFunction updateModelAnimation__12LivingEntityFv;
    undefinedFunction getSpeed__6PlayerFv;
    undefinedFunction setSpeed__12LivingEntityFf;
    undefinedFunction doHurtTarget__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction isSleeping__6PlayerFv;
    undefinedFunction tickHeadTurn__12LivingEntityFfT1;
    undefinedFunction aiStep__6PlayerFv;
    undefinedFunction serverAiStep__6PlayerFv;
    undefinedFunction pushEntities__6PlayerFv;
    undefinedFunction doPush__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction setJumping__12LivingEntityFb;
    undefinedFunction take__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entityi;
    undefinedFunction canSee__12LivingEntityFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction getAttackAnim__12LivingEntityFf;
    undefinedFunction getSweptVolume__12LivingEntityFv;
    undefinedFunction isEffectiveAi__12LivingEntityFv;
    undefinedFunction getAbsorptionAmount__6PlayerFv;
    undefinedFunction setAbsorptionAmount__6PlayerFf;
    undefinedFunction onEnterCombat__12LivingEntityFv;
    undefinedFunction onLeaveCombat__12LivingEntityFv;
    undefinedFunction updateEffectVisibility__12LivingEntityFv;
    undefinedFunction getMainArm__6PlayerFv;
    undefinedFunction isUsingItem__12LivingEntityFv;
    undefinedFunction getUsedItemHand__12LivingEntityFv;
    undefinedFunction updatingUsingItem__12LivingEntityFv;
    undefinedFunction startUsingItem__12LivingEntityFQ2_15InteractionHand16EInteractionHand;
    undefinedFunction spawnItemUseParticles__12LivingEntityF35not_null_ptr__tm__15_12ItemInstancei;
    undefinedFunction completeUsingItem__12LivingEntityFv;
    undefinedFunction getTicksUsingItem__12LivingEntityFv;
    undefinedFunction releaseUsingItem__12LivingEntityFv;
    undefinedFunction releaseUsingItem__12LivingEntityFi;
    undefinedFunction stopUsingItem__12LivingEntityFv;
    undefinedFunction isBlocking__12LivingEntityFv;
    undefinedFunction isFallFlying__12LivingEntityFv;
    undefinedFunction getFallFlyingTicks__12LivingEntityFv;
    undefinedFunction isAffectedByPotions__12LivingEntityFv;
    undefinedFunction attackable__12LivingEntityFv;
    undefinedFunction setRecordPlayingNearby__12LivingEntityFRC8BlockPosb;
    undefinedFunction IsCreativeFlying__6PlayerFv;
    undefinedFunction updateFrameTick__6PlayerFv;
    undefinedFunction closeContainer__6PlayerFv;
    undefinedFunction touch__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction getScore__6PlayerFv;
    undefinedFunction setScore__6PlayerFi;
    undefinedFunction increaseScore__6PlayerFi;
    undefinedFunction drop__6PlayerFb;
    undefinedFunction reallyDrop__6PlayerFQ2_5boost31shared_ptr__tm__13_10ItemEntity;
    undefinedFunction GetThirdPersonView__6PlayerFb;
    undefinedFunction SetThirdPersonView__6PlayerFi;
    undefinedFunction CanChangeThirdPersonView__6PlayerFv;
    undefinedFunction GetCameraController__6PlayerFv;
    undefinedFunction SetCameraController__6PlayerFP16CameraControllerb;
    undefinedFunction canHarmPlayer__6PlayerFQ2_5boost25shared_ptr__tm__8_6Player;
    undefinedFunction canHarmPlayer__6PlayerFQ2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_w;
    undefinedFunction getArmorCoverPercentage__6PlayerFv;
    undefinedFunction openTextEdit__6PlayerFQ2_5boost36shared_ptr__tm__18_15SignBlockEntity;
    undefinedFunction openMinecartCommandBlock__6PlayerFQ2_5boost37shared_ptr__tm__19_16BaseCommandBlock;
    undefinedFunction openCommandBlock__6PlayerFQ2_5boost39shared_ptr__tm__21_18CommandBlockEntity;
    undefinedFunction openTrading__6PlayerFQ2_5boost28shared_ptr__tm__10_8MerchantRCQ2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wi;
    undefinedFunction openContainer__6PlayerFQ2_5boost29shared_ptr__tm__11_9Container;
    undefinedFunction openHorseInventory__6PlayerFQ2_5boost34shared_ptr__tm__16_13AbstractHorseQ2_5boost29shared_ptr__tm__11_9Container;
    undefinedFunction startBlockInteraction__6PlayerFR17InteractionObject;
    undefinedFunction openItemInstanceGui__6PlayerF35not_null_ptr__tm__15_12ItemInstanceQ2_15InteractionHand16EInteractionHand;
    undefinedFunction interactOn__6PlayerFQ2_5boost25shared_ptr__tm__8_6EntityQ2_15InteractionHand16EInteractionHand;
    undefinedFunction attack__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction disableShield__6PlayerFb;
    undefinedFunction crit__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction magicCrit__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction respawn__6PlayerFv;
    undefinedFunction isLocalPlayer__6PlayerFv;
    undefinedFunction getGameProfile__6PlayerFv;
    undefinedFunction startSleepInBed__6PlayerFRC8BlockPosb;
    undefinedFunction stopSleepInBed__6PlayerFbN21;
    undefinedFunction displayClientMessage__6PlayerFib;
    undefinedFunction getRespawnPosition__6PlayerFv;
    undefinedFunction isRespawnForced__6PlayerFv;
    undefinedFunction setRespawnPosition__6PlayerFP8BlockPosb;
    undefinedFunction hasAchievement__6PlayerFP11Achievement;
    undefinedFunction awardStat__6PlayerFP4Stat25arrayWithLength__tm__3_Uc;
    undefinedFunction resetStat__6PlayerFP4Stat;
    undefinedFunction checkMovementStatistiscs__6PlayerFdN21;
    undefinedFunction increaseXp__6PlayerFi;
    undefinedFunction getEnchantmentSeed__6PlayerFv;
    undefinedFunction onEnchantmentPerformed__6PlayerFi;
    undefinedFunction giveExperienceLevels__6PlayerFi;
    undefinedFunction mayBuild__6PlayerFv;
    undefinedFunction mayUseItemAt__6PlayerFRC8BlockPosPC9Direction35not_null_ptr__tm__15_12ItemInstance;
    undefinedFunction onUpdateAbilities__6PlayerFv;
    undefinedFunction setGameMode__6PlayerFPC8GameType;
    undefinedFunction __pure_virtual_called;
    undefinedFunction GetScoreboard__6PlayerFv;
    undefinedFunction onCrafted__6PlayerF35not_null_ptr__tm__15_12ItemInstance;
    undefinedFunction getTexture__6PlayerFv;
    undefinedFunction setCustomSkin__6PlayerFUi;
    undefinedFunction setCustomCape__6PlayerFUi;
    undefinedFunction handleCollectItem__6PlayerF35not_null_ptr__tm__15_12ItemInstance;
    undefinedFunction SetCamera__6PlayerFQ2_5boost25shared_ptr__tm__8_6Entity;
    undefinedFunction SpectatePlayerNext__6PlayerFv;
    undefinedFunction SpectatePlayerPrev__6PlayerFv;
    undefinedFunction StopSpectatingPlayer__6PlayerFv;
    undefinedFunction IsSpectatingOtherPlayer__6PlayerFv;
    undefinedFunction __pure_virtual_called2;
    undefinedFunction GetGameMode__6PlayerFv;



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