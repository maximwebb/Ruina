#pragma once

class Event {};

class OnLogRequestEvent : public Event {};

class OnRenderEvent : public Event {};

class OnGameTickEvent : public Event {};