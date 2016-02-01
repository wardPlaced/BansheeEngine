//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsPhysXPrerequisites.h"
#include "BsPhysics.h"
#include "BSCollision.h"
#include "PxPhysics.h"
#include "foundation/Px.h"
#include "cooking/PxCooking.h"

namespace BansheeEngine
{
	class PhysX : public Physics
	{
		enum class ContactEventType
		{
			ContactStart,
			ContactStay,
			ContactStop
		};

		struct TriggerEvent
		{
			Collider* trigger;
			Collider* other;
			ContactEventType type;
		};

		struct ContactEvent
		{
			Collider* colliderA;
			Collider* colliderB;
			ContactEventType type;
			Vector<ContactPoint> points;
		};

	public:
		PhysX();
		~PhysX();

		void update() override;

		SPtr<PhysicsMaterial> createMaterial(float staticFriction, float dynamicFriction, float restitution) override;
		SPtr<Rigidbody> createRigidbody(const Vector3& position = Vector3::ZERO,
			const Quaternion& rotation = Quaternion::IDENTITY) override;

		SPtr<BoxCollider> createBoxCollider(float extentX, float extentY, float extentZ, const Vector3& position, 
			const Quaternion& rotation) override;
		SPtr<SphereCollider> createSphereCollider(float radius, const Vector3& position, const Quaternion& rotation) override;
		SPtr<PlaneCollider> createPlaneCollider(const Vector3& position, const Quaternion& rotation) override;
		SPtr<CapsuleCollider> createCapsuleCollider(float radius, float halfHeight, const Vector3& position, 
			const Quaternion& rotation) override;

		void _reportContactEvent(const ContactEvent& event);
		void _reportTriggerEvent(const TriggerEvent& event);

		physx::PxMaterial* getDefaultMaterial() const { return mDefaultMaterial; }
		physx::PxPhysics* getPhysX() const { return mPhysics; }
		physx::PxScene* getScene() const { return mScene; }

	private:
		friend class PhysXEventCallback;

		float mSimulationStep = 1.0f/60.0f;
		float mLastSimulationTime = 0.0f;

		Vector<TriggerEvent> mTriggerEvents;
		Vector<ContactEvent> mContactEvents;

		physx::PxFoundation* mFoundation = nullptr;
		physx::PxPhysics* mPhysics = nullptr;
		physx::PxCooking* mCooking = nullptr;
		physx::PxScene* mScene = nullptr;

		physx::PxMaterial* mDefaultMaterial = nullptr;
	};

	/** Provides easier access to PhysX. */
	PhysX& gPhysX();
}